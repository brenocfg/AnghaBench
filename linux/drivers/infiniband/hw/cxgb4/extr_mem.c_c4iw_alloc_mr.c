#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ib_mr {int rkey; int lkey; } ;
struct c4iw_pd {int /*<<< orphan*/  pdid; struct c4iw_dev* rhp; } ;
struct TYPE_7__ {int pbl_size; int stag; int /*<<< orphan*/  pbl_addr; scalar_t__ state; int /*<<< orphan*/  type; int /*<<< orphan*/  pdid; } ;
struct c4iw_mr {int max_mpl_len; int /*<<< orphan*/  wr_waitp; int /*<<< orphan*/  mpl_addr; int /*<<< orphan*/  mpl; struct c4iw_dev* rhp; TYPE_1__ attr; int /*<<< orphan*/  dereg_skb; struct ib_mr ibmr; } ;
struct TYPE_9__ {TYPE_2__* pdev; scalar_t__ ulptx_memwrite_dsgl; } ;
struct TYPE_10__ {TYPE_3__ lldi; } ;
struct c4iw_dev {TYPE_4__ rdev; int /*<<< orphan*/  mrs; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  FW_RI_STAG_NSMR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_MR_TYPE_MEM_REG ; 
 int alloc_pbl (struct c4iw_mr*,int) ; 
 int allocate_stag (TYPE_4__*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_alloc_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_init_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_pblpool_free (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c4iw_put_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dereg_mem (TYPE_4__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c4iw_mr*) ; 
 struct c4iw_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,struct c4iw_mr*,int) ; 
 int roundup (int,int) ; 
 int t4_max_fr_depth (int) ; 
 struct c4iw_pd* to_c4iw_pd (struct ib_pd*) ; 
 scalar_t__ use_dsgl ; 
 scalar_t__ xa_insert_irq (int /*<<< orphan*/ *,int,struct c4iw_mr*,int /*<<< orphan*/ ) ; 

struct ib_mr *c4iw_alloc_mr(struct ib_pd *pd, enum ib_mr_type mr_type,
			    u32 max_num_sg, struct ib_udata *udata)
{
	struct c4iw_dev *rhp;
	struct c4iw_pd *php;
	struct c4iw_mr *mhp;
	u32 mmid;
	u32 stag = 0;
	int ret = 0;
	int length = roundup(max_num_sg * sizeof(u64), 32);

	php = to_c4iw_pd(pd);
	rhp = php->rhp;

	if (mr_type != IB_MR_TYPE_MEM_REG ||
	    max_num_sg > t4_max_fr_depth(rhp->rdev.lldi.ulptx_memwrite_dsgl &&
					 use_dsgl))
		return ERR_PTR(-EINVAL);

	mhp = kzalloc(sizeof(*mhp), GFP_KERNEL);
	if (!mhp) {
		ret = -ENOMEM;
		goto err;
	}

	mhp->wr_waitp = c4iw_alloc_wr_wait(GFP_KERNEL);
	if (!mhp->wr_waitp) {
		ret = -ENOMEM;
		goto err_free_mhp;
	}
	c4iw_init_wr_wait(mhp->wr_waitp);

	mhp->mpl = dma_alloc_coherent(&rhp->rdev.lldi.pdev->dev,
				      length, &mhp->mpl_addr, GFP_KERNEL);
	if (!mhp->mpl) {
		ret = -ENOMEM;
		goto err_free_wr_wait;
	}
	mhp->max_mpl_len = length;

	mhp->rhp = rhp;
	ret = alloc_pbl(mhp, max_num_sg);
	if (ret)
		goto err_free_dma;
	mhp->attr.pbl_size = max_num_sg;
	ret = allocate_stag(&rhp->rdev, &stag, php->pdid,
			    mhp->attr.pbl_size, mhp->attr.pbl_addr,
			    mhp->wr_waitp);
	if (ret)
		goto err_free_pbl;
	mhp->attr.pdid = php->pdid;
	mhp->attr.type = FW_RI_STAG_NSMR;
	mhp->attr.stag = stag;
	mhp->attr.state = 0;
	mmid = (stag) >> 8;
	mhp->ibmr.rkey = mhp->ibmr.lkey = stag;
	if (xa_insert_irq(&rhp->mrs, mmid, mhp, GFP_KERNEL)) {
		ret = -ENOMEM;
		goto err_dereg;
	}

	pr_debug("mmid 0x%x mhp %p stag 0x%x\n", mmid, mhp, stag);
	return &(mhp->ibmr);
err_dereg:
	dereg_mem(&rhp->rdev, stag, mhp->attr.pbl_size,
		  mhp->attr.pbl_addr, mhp->dereg_skb, mhp->wr_waitp);
err_free_pbl:
	c4iw_pblpool_free(&mhp->rhp->rdev, mhp->attr.pbl_addr,
			      mhp->attr.pbl_size << 3);
err_free_dma:
	dma_free_coherent(&mhp->rhp->rdev.lldi.pdev->dev,
			  mhp->max_mpl_len, mhp->mpl, mhp->mpl_addr);
err_free_wr_wait:
	c4iw_put_wr_wait(mhp->wr_waitp);
err_free_mhp:
	kfree(mhp);
err:
	return ERR_PTR(ret);
}