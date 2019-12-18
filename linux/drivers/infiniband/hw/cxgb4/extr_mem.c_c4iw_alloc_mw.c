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
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ib_mw {int rkey; } ;
struct c4iw_pd {int /*<<< orphan*/  pdid; struct c4iw_dev* rhp; } ;
struct TYPE_2__ {int stag; int /*<<< orphan*/  type; int /*<<< orphan*/  pdid; } ;
struct c4iw_mw {int /*<<< orphan*/  wr_waitp; int /*<<< orphan*/  dereg_skb; TYPE_1__ attr; struct ib_mw ibmw; struct c4iw_dev* rhp; } ;
struct c4iw_dev {int /*<<< orphan*/  rdev; int /*<<< orphan*/  mrs; } ;
typedef  enum ib_mw_type { ____Placeholder_ib_mw_type } ib_mw_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_mw* ERR_PTR (int) ; 
 int /*<<< orphan*/  FW_RI_STAG_MW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_MW_TYPE_1 ; 
 int /*<<< orphan*/  SGE_MAX_WR_LEN ; 
 int /*<<< orphan*/  alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int allocate_window (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_alloc_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_put_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deallocate_window (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c4iw_mw*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 struct c4iw_mw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,struct c4iw_mw*,int) ; 
 struct c4iw_pd* to_c4iw_pd (struct ib_pd*) ; 
 scalar_t__ xa_insert_irq (int /*<<< orphan*/ *,int,struct c4iw_mw*,int /*<<< orphan*/ ) ; 

struct ib_mw *c4iw_alloc_mw(struct ib_pd *pd, enum ib_mw_type type,
			    struct ib_udata *udata)
{
	struct c4iw_dev *rhp;
	struct c4iw_pd *php;
	struct c4iw_mw *mhp;
	u32 mmid;
	u32 stag = 0;
	int ret;

	if (type != IB_MW_TYPE_1)
		return ERR_PTR(-EINVAL);

	php = to_c4iw_pd(pd);
	rhp = php->rhp;
	mhp = kzalloc(sizeof(*mhp), GFP_KERNEL);
	if (!mhp)
		return ERR_PTR(-ENOMEM);

	mhp->wr_waitp = c4iw_alloc_wr_wait(GFP_KERNEL);
	if (!mhp->wr_waitp) {
		ret = -ENOMEM;
		goto free_mhp;
	}

	mhp->dereg_skb = alloc_skb(SGE_MAX_WR_LEN, GFP_KERNEL);
	if (!mhp->dereg_skb) {
		ret = -ENOMEM;
		goto free_wr_wait;
	}

	ret = allocate_window(&rhp->rdev, &stag, php->pdid, mhp->wr_waitp);
	if (ret)
		goto free_skb;
	mhp->rhp = rhp;
	mhp->attr.pdid = php->pdid;
	mhp->attr.type = FW_RI_STAG_MW;
	mhp->attr.stag = stag;
	mmid = (stag) >> 8;
	mhp->ibmw.rkey = stag;
	if (xa_insert_irq(&rhp->mrs, mmid, mhp, GFP_KERNEL)) {
		ret = -ENOMEM;
		goto dealloc_win;
	}
	pr_debug("mmid 0x%x mhp %p stag 0x%x\n", mmid, mhp, stag);
	return &(mhp->ibmw);

dealloc_win:
	deallocate_window(&rhp->rdev, mhp->attr.stag, mhp->dereg_skb,
			  mhp->wr_waitp);
free_skb:
	kfree_skb(mhp->dereg_skb);
free_wr_wait:
	c4iw_put_wr_wait(mhp->wr_waitp);
free_mhp:
	kfree(mhp);
	return ERR_PTR(ret);
}