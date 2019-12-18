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
struct ib_pd {int dummy; } ;
struct ib_mr {int dummy; } ;
struct c4iw_pd {int /*<<< orphan*/  pdid; struct c4iw_dev* rhp; } ;
struct TYPE_2__ {int mw_bind_enable; unsigned long long len; int /*<<< orphan*/  pbl_addr; scalar_t__ pbl_size; int /*<<< orphan*/  stag; int /*<<< orphan*/  perms; scalar_t__ page_size; scalar_t__ va_fbo; scalar_t__ zbva; int /*<<< orphan*/  pdid; } ;
struct c4iw_mr {int /*<<< orphan*/  wr_waitp; int /*<<< orphan*/  dereg_skb; TYPE_1__ attr; struct ib_mr ibmr; struct c4iw_dev* rhp; } ;
struct c4iw_dev {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  FW_RI_STAG_NSMR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_MW_BIND ; 
 int /*<<< orphan*/  SGE_MAX_WR_LEN ; 
 int /*<<< orphan*/  T4_STAG_UNSET ; 
 int /*<<< orphan*/  alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_alloc_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_ib_to_tpt_access (int) ; 
 int /*<<< orphan*/  c4iw_init_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_put_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dereg_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int finish_mem_reg (struct c4iw_mr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c4iw_mr*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 struct c4iw_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct ib_pd*) ; 
 struct c4iw_pd* to_c4iw_pd (struct ib_pd*) ; 
 int write_tpt_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct ib_mr *c4iw_get_dma_mr(struct ib_pd *pd, int acc)
{
	struct c4iw_dev *rhp;
	struct c4iw_pd *php;
	struct c4iw_mr *mhp;
	int ret;
	u32 stag = T4_STAG_UNSET;

	pr_debug("ib_pd %p\n", pd);
	php = to_c4iw_pd(pd);
	rhp = php->rhp;

	mhp = kzalloc(sizeof(*mhp), GFP_KERNEL);
	if (!mhp)
		return ERR_PTR(-ENOMEM);
	mhp->wr_waitp = c4iw_alloc_wr_wait(GFP_KERNEL);
	if (!mhp->wr_waitp) {
		ret = -ENOMEM;
		goto err_free_mhp;
	}
	c4iw_init_wr_wait(mhp->wr_waitp);

	mhp->dereg_skb = alloc_skb(SGE_MAX_WR_LEN, GFP_KERNEL);
	if (!mhp->dereg_skb) {
		ret = -ENOMEM;
		goto err_free_wr_wait;
	}

	mhp->rhp = rhp;
	mhp->attr.pdid = php->pdid;
	mhp->attr.perms = c4iw_ib_to_tpt_access(acc);
	mhp->attr.mw_bind_enable = (acc&IB_ACCESS_MW_BIND) == IB_ACCESS_MW_BIND;
	mhp->attr.zbva = 0;
	mhp->attr.va_fbo = 0;
	mhp->attr.page_size = 0;
	mhp->attr.len = ~0ULL;
	mhp->attr.pbl_size = 0;

	ret = write_tpt_entry(&rhp->rdev, 0, &stag, 1, php->pdid,
			      FW_RI_STAG_NSMR, mhp->attr.perms,
			      mhp->attr.mw_bind_enable, 0, 0, ~0ULL, 0, 0, 0,
			      NULL, mhp->wr_waitp);
	if (ret)
		goto err_free_skb;

	ret = finish_mem_reg(mhp, stag);
	if (ret)
		goto err_dereg_mem;
	return &mhp->ibmr;
err_dereg_mem:
	dereg_mem(&rhp->rdev, mhp->attr.stag, mhp->attr.pbl_size,
		  mhp->attr.pbl_addr, mhp->dereg_skb, mhp->wr_waitp);
err_free_skb:
	kfree_skb(mhp->dereg_skb);
err_free_wr_wait:
	c4iw_put_wr_wait(mhp->wr_waitp);
err_free_mhp:
	kfree(mhp);
	return ERR_PTR(ret);
}