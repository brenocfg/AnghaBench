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
struct ntb_dev {int /*<<< orphan*/  ctx_lock; struct ntb_ctx_ops const* ctx_ops; void* ctx; } ;
struct ntb_ctx_ops {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ntb_ctx_ops_is_valid (struct ntb_ctx_ops const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ntb_set_ctx(struct ntb_dev *ntb, void *ctx,
		const struct ntb_ctx_ops *ctx_ops)
{
	unsigned long irqflags;

	if (!ntb_ctx_ops_is_valid(ctx_ops))
		return -EINVAL;
	if (ntb->ctx_ops)
		return -EINVAL;

	spin_lock_irqsave(&ntb->ctx_lock, irqflags);
	{
		ntb->ctx = ctx;
		ntb->ctx_ops = ctx_ops;
	}
	spin_unlock_irqrestore(&ntb->ctx_lock, irqflags);

	return 0;
}