#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ state; } ;
struct c4iw_mr {TYPE_1__ attr; } ;
struct c4iw_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct c4iw_mr* get_mhp (struct c4iw_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void c4iw_invalidate_mr(struct c4iw_dev *rhp, u32 rkey)
{
	struct c4iw_mr *mhp;
	unsigned long flags;

	spin_lock_irqsave(&rhp->lock, flags);
	mhp = get_mhp(rhp, rkey >> 8);
	if (mhp)
		mhp->attr.state = 0;
	spin_unlock_irqrestore(&rhp->lock, flags);
}