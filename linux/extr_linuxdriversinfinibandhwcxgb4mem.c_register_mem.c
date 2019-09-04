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
typedef  int /*<<< orphan*/  u32 ;
struct c4iw_pd {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  pbl_addr; int /*<<< orphan*/  pbl_size; int /*<<< orphan*/  stag; int /*<<< orphan*/  va_fbo; int /*<<< orphan*/  zbva; int /*<<< orphan*/  mw_bind_enable; int /*<<< orphan*/  perms; int /*<<< orphan*/  pdid; } ;
struct c4iw_mr {int /*<<< orphan*/ * dereg_skb; int /*<<< orphan*/  wr_waitp; TYPE_1__ attr; } ;
struct c4iw_dev {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_RI_STAG_NSMR ; 
 int /*<<< orphan*/  T4_STAG_UNSET ; 
 int /*<<< orphan*/  dereg_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int finish_mem_reg (struct c4iw_mr*,int /*<<< orphan*/ ) ; 
 int write_tpt_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int register_mem(struct c4iw_dev *rhp, struct c4iw_pd *php,
		      struct c4iw_mr *mhp, int shift)
{
	u32 stag = T4_STAG_UNSET;
	int ret;

	ret = write_tpt_entry(&rhp->rdev, 0, &stag, 1, mhp->attr.pdid,
			      FW_RI_STAG_NSMR, mhp->attr.len ?
			      mhp->attr.perms : 0,
			      mhp->attr.mw_bind_enable, mhp->attr.zbva,
			      mhp->attr.va_fbo, mhp->attr.len ?
			      mhp->attr.len : -1, shift - 12,
			      mhp->attr.pbl_size, mhp->attr.pbl_addr, NULL,
			      mhp->wr_waitp);
	if (ret)
		return ret;

	ret = finish_mem_reg(mhp, stag);
	if (ret) {
		dereg_mem(&rhp->rdev, mhp->attr.stag, mhp->attr.pbl_size,
			  mhp->attr.pbl_addr, mhp->dereg_skb, mhp->wr_waitp);
		mhp->dereg_skb = NULL;
	}
	return ret;
}