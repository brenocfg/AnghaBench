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
struct ib_mw {int rkey; } ;
struct TYPE_2__ {int /*<<< orphan*/  stag; } ;
struct c4iw_mw {int /*<<< orphan*/  wr_waitp; int /*<<< orphan*/  dereg_skb; TYPE_1__ attr; struct c4iw_dev* rhp; } ;
struct c4iw_dev {int /*<<< orphan*/  rdev; int /*<<< orphan*/  mrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_put_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deallocate_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c4iw_mw*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct ib_mw*,int,struct c4iw_mw*) ; 
 struct c4iw_mw* to_c4iw_mw (struct ib_mw*) ; 
 int /*<<< orphan*/  xa_erase_irq (int /*<<< orphan*/ *,int) ; 

int c4iw_dealloc_mw(struct ib_mw *mw)
{
	struct c4iw_dev *rhp;
	struct c4iw_mw *mhp;
	u32 mmid;

	mhp = to_c4iw_mw(mw);
	rhp = mhp->rhp;
	mmid = (mw->rkey) >> 8;
	xa_erase_irq(&rhp->mrs, mmid);
	deallocate_window(&rhp->rdev, mhp->attr.stag, mhp->dereg_skb,
			  mhp->wr_waitp);
	kfree_skb(mhp->dereg_skb);
	c4iw_put_wr_wait(mhp->wr_waitp);
	pr_debug("ib_mw %p mmid 0x%x ptr %p\n", mw, mmid, mhp);
	kfree(mhp);
	return 0;
}