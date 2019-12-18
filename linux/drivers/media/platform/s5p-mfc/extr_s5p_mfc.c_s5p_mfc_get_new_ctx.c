#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct s5p_mfc_dev {int curr_ctx; int /*<<< orphan*/  condlock; int /*<<< orphan*/  ctx_work_bits; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MFC_NUM_CONTEXTS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ *) ; 

int s5p_mfc_get_new_ctx(struct s5p_mfc_dev *dev)
{
	unsigned long flags;
	int ctx;

	spin_lock_irqsave(&dev->condlock, flags);
	ctx = dev->curr_ctx;
	do {
		ctx = (ctx + 1) % MFC_NUM_CONTEXTS;
		if (ctx == dev->curr_ctx) {
			if (!test_bit(ctx, &dev->ctx_work_bits))
				ctx = -EAGAIN;
			break;
		}
	} while (!test_bit(ctx, &dev->ctx_work_bits));
	spin_unlock_irqrestore(&dev->condlock, flags);

	return ctx;
}