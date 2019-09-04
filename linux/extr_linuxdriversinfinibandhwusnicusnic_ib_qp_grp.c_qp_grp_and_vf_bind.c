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
struct usnic_ib_vf {scalar_t__ qp_grp_ref_cnt; struct usnic_ib_pd* pd; int /*<<< orphan*/  vnic; int /*<<< orphan*/  lock; } ;
struct usnic_ib_qp_grp {struct usnic_ib_vf* vf; } ;
struct usnic_ib_pd {int /*<<< orphan*/  umem_pd; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ) ; 
 int usnic_uiom_attach_dev_to_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_dev* usnic_vnic_get_pdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qp_grp_and_vf_bind(struct usnic_ib_vf *vf,
				struct usnic_ib_pd *pd,
				struct usnic_ib_qp_grp *qp_grp)
{
	int err;
	struct pci_dev *pdev;

	lockdep_assert_held(&vf->lock);

	pdev = usnic_vnic_get_pdev(vf->vnic);
	if (vf->qp_grp_ref_cnt == 0) {
		err = usnic_uiom_attach_dev_to_pd(pd->umem_pd, &pdev->dev);
		if (err) {
			usnic_err("Failed to attach %s to domain\n",
					pci_name(pdev));
			return err;
		}
		vf->pd = pd;
	}
	vf->qp_grp_ref_cnt++;

	WARN_ON(vf->pd != pd);
	qp_grp->vf = vf;

	return 0;
}