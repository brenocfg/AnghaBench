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
struct bnxt_ulp_ops {int /*<<< orphan*/  (* ulp_irq_restart ) (int /*<<< orphan*/ ,struct bnxt_msix_entry*) ;} ;
struct bnxt_ulp {int /*<<< orphan*/  handle; int /*<<< orphan*/  msix_requested; int /*<<< orphan*/  ulp_ops; } ;
struct bnxt_msix_entry {int dummy; } ;
struct bnxt_en_dev {int flags; struct bnxt_ulp* ulp_tbl; } ;
struct bnxt {struct bnxt_en_dev* edev; } ;

/* Variables and functions */
 int BNXT_EN_FLAG_MSIX_REQUESTED ; 
 size_t BNXT_ROCE_ULP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bnxt_fill_msix_vecs (struct bnxt*,struct bnxt_msix_entry*) ; 
 scalar_t__ bnxt_ulp_registered (struct bnxt_en_dev*,size_t) ; 
 struct bnxt_msix_entry* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bnxt_msix_entry*) ; 
 struct bnxt_ulp_ops* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bnxt_msix_entry*) ; 

void bnxt_ulp_irq_restart(struct bnxt *bp, int err)
{
	struct bnxt_en_dev *edev = bp->edev;
	struct bnxt_ulp_ops *ops;

	if (!edev || !(edev->flags & BNXT_EN_FLAG_MSIX_REQUESTED))
		return;

	if (bnxt_ulp_registered(bp->edev, BNXT_ROCE_ULP)) {
		struct bnxt_ulp *ulp = &edev->ulp_tbl[BNXT_ROCE_ULP];
		struct bnxt_msix_entry *ent = NULL;

		if (!ulp->msix_requested)
			return;

		ops = rtnl_dereference(ulp->ulp_ops);
		if (!ops || !ops->ulp_irq_restart)
			return;

		if (!err) {
			ent = kcalloc(ulp->msix_requested, sizeof(*ent),
				      GFP_KERNEL);
			if (!ent)
				return;
			bnxt_fill_msix_vecs(bp, ent);
		}
		ops->ulp_irq_restart(ulp->handle, ent);
		kfree(ent);
	}
}