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
struct bnxt_ulp_ops {int /*<<< orphan*/  (* ulp_sriov_config ) (int /*<<< orphan*/ ,int) ;} ;
struct bnxt_ulp {int /*<<< orphan*/  handle; int /*<<< orphan*/  ulp_ops; } ;
struct bnxt_en_dev {struct bnxt_ulp* ulp_tbl; } ;
struct bnxt {struct bnxt_en_dev* edev; } ;

/* Variables and functions */
 int BNXT_MAX_ULP ; 
 int /*<<< orphan*/  bnxt_ulp_get (struct bnxt_ulp*) ; 
 int /*<<< orphan*/  bnxt_ulp_put (struct bnxt_ulp*) ; 
 struct bnxt_ulp_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

void bnxt_ulp_sriov_cfg(struct bnxt *bp, int num_vfs)
{
	struct bnxt_en_dev *edev = bp->edev;
	struct bnxt_ulp_ops *ops;
	int i;

	if (!edev)
		return;

	for (i = 0; i < BNXT_MAX_ULP; i++) {
		struct bnxt_ulp *ulp = &edev->ulp_tbl[i];

		rcu_read_lock();
		ops = rcu_dereference(ulp->ulp_ops);
		if (!ops || !ops->ulp_sriov_config) {
			rcu_read_unlock();
			continue;
		}
		bnxt_ulp_get(ulp);
		rcu_read_unlock();
		ops->ulp_sriov_config(ulp->handle, num_vfs);
		bnxt_ulp_put(ulp);
	}
}