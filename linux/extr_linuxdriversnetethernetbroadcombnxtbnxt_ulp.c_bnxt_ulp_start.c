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
struct bnxt_ulp_ops {int /*<<< orphan*/  (* ulp_start ) (int /*<<< orphan*/ ) ;} ;
struct bnxt_ulp {int /*<<< orphan*/  handle; int /*<<< orphan*/  ulp_ops; } ;
struct bnxt_en_dev {struct bnxt_ulp* ulp_tbl; } ;
struct bnxt {struct bnxt_en_dev* edev; } ;

/* Variables and functions */
 int BNXT_MAX_ULP ; 
 struct bnxt_ulp_ops* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void bnxt_ulp_start(struct bnxt *bp)
{
	struct bnxt_en_dev *edev = bp->edev;
	struct bnxt_ulp_ops *ops;
	int i;

	if (!edev)
		return;

	for (i = 0; i < BNXT_MAX_ULP; i++) {
		struct bnxt_ulp *ulp = &edev->ulp_tbl[i];

		ops = rtnl_dereference(ulp->ulp_ops);
		if (!ops || !ops->ulp_start)
			continue;
		ops->ulp_start(ulp->handle);
	}
}