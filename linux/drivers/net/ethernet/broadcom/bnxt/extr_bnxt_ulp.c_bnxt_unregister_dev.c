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
struct net_device {int dummy; } ;
struct bnxt_ulp {int /*<<< orphan*/  ref_count; int /*<<< orphan*/ * async_events_bmap; scalar_t__ max_async_event_id; int /*<<< orphan*/  ulp_ops; scalar_t__ msix_requested; } ;
struct bnxt_en_dev {TYPE_1__* en_ops; struct bnxt_ulp* ulp_tbl; struct net_device* net; } ;
struct bnxt {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bnxt_free_msix ) (struct bnxt_en_dev*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int BNXT_MAX_ULP ; 
 int BNXT_ROCE_ULP ; 
 int EINVAL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_hwrm_func_rgtr_async_events (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct bnxt_en_dev*,int) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int bnxt_unregister_dev(struct bnxt_en_dev *edev, int ulp_id)
{
	struct net_device *dev = edev->net;
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_ulp *ulp;
	int i = 0;

	ASSERT_RTNL();
	if (ulp_id >= BNXT_MAX_ULP)
		return -EINVAL;

	ulp = &edev->ulp_tbl[ulp_id];
	if (!rcu_access_pointer(ulp->ulp_ops)) {
		netdev_err(bp->dev, "ulp id %d not registered\n", ulp_id);
		return -EINVAL;
	}
	if (ulp_id == BNXT_ROCE_ULP && ulp->msix_requested)
		edev->en_ops->bnxt_free_msix(edev, ulp_id);

	if (ulp->max_async_event_id)
		bnxt_hwrm_func_rgtr_async_events(bp, NULL, 0);

	RCU_INIT_POINTER(ulp->ulp_ops, NULL);
	synchronize_rcu();
	ulp->max_async_event_id = 0;
	ulp->async_events_bmap = NULL;
	while (atomic_read(&ulp->ref_count) != 0 && i < 10) {
		msleep(100);
		i++;
	}
	return 0;
}