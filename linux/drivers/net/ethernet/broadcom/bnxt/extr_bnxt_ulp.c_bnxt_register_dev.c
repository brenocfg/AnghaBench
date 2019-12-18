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
struct net_device {int dummy; } ;
struct bnxt_ulp_ops {int dummy; } ;
struct bnxt_ulp {int /*<<< orphan*/  ulp_ops; void* handle; int /*<<< orphan*/  ref_count; } ;
struct bnxt_en_dev {struct bnxt_ulp* ulp_tbl; struct net_device* net; } ;
struct bnxt {unsigned int cp_nr_rings; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int BNXT_MAX_ULP ; 
 unsigned int BNXT_MIN_ROCE_STAT_CTXS ; 
 int BNXT_ROCE_ULP ; 
 int /*<<< orphan*/  BNXT_STATE_OPEN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int bnxt_get_max_func_stat_ctxs (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_vnic_cfg (struct bnxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct bnxt_ulp_ops*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_register_dev(struct bnxt_en_dev *edev, int ulp_id,
			     struct bnxt_ulp_ops *ulp_ops, void *handle)
{
	struct net_device *dev = edev->net;
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_ulp *ulp;

	ASSERT_RTNL();
	if (ulp_id >= BNXT_MAX_ULP)
		return -EINVAL;

	ulp = &edev->ulp_tbl[ulp_id];
	if (rcu_access_pointer(ulp->ulp_ops)) {
		netdev_err(bp->dev, "ulp id %d already registered\n", ulp_id);
		return -EBUSY;
	}
	if (ulp_id == BNXT_ROCE_ULP) {
		unsigned int max_stat_ctxs;

		max_stat_ctxs = bnxt_get_max_func_stat_ctxs(bp);
		if (max_stat_ctxs <= BNXT_MIN_ROCE_STAT_CTXS ||
		    bp->cp_nr_rings == max_stat_ctxs)
			return -ENOMEM;
	}

	atomic_set(&ulp->ref_count, 0);
	ulp->handle = handle;
	rcu_assign_pointer(ulp->ulp_ops, ulp_ops);

	if (ulp_id == BNXT_ROCE_ULP) {
		if (test_bit(BNXT_STATE_OPEN, &bp->state))
			bnxt_hwrm_vnic_cfg(bp, 0);
	}

	return 0;
}