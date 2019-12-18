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
struct usnic_ib_qp_grp {TYPE_1__* vf; } ;
struct usnic_ib_pd {int /*<<< orphan*/  umem_pd; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ qp_grp_ref_cnt; struct usnic_ib_pd* pd; int /*<<< orphan*/  vnic; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_uiom_detach_dev_from_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_dev* usnic_vnic_get_pdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qp_grp_and_vf_unbind(struct usnic_ib_qp_grp *qp_grp)
{
	struct pci_dev *pdev;
	struct usnic_ib_pd *pd;

	lockdep_assert_held(&qp_grp->vf->lock);

	pd = qp_grp->vf->pd;
	pdev = usnic_vnic_get_pdev(qp_grp->vf->vnic);
	if (--qp_grp->vf->qp_grp_ref_cnt == 0) {
		qp_grp->vf->pd = NULL;
		usnic_uiom_detach_dev_from_pd(pd->umem_pd, &pdev->dev);
	}
	qp_grp->vf = NULL;
}