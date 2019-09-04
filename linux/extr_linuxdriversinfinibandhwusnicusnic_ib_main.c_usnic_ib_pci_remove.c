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
struct usnic_ib_vf {int /*<<< orphan*/  vnic; int /*<<< orphan*/  link; struct usnic_ib_dev* pf; } ;
struct usnic_ib_dev {int /*<<< orphan*/  vf_cnt; int /*<<< orphan*/  usdev_lock; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usnic_ib_vf*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct usnic_ib_vf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_ib_undiscover_pf ; 
 int /*<<< orphan*/  usnic_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_vnic_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usnic_ib_pci_remove(struct pci_dev *pdev)
{
	struct usnic_ib_vf *vf = pci_get_drvdata(pdev);
	struct usnic_ib_dev *pf = vf->pf;

	mutex_lock(&pf->usdev_lock);
	list_del(&vf->link);
	mutex_unlock(&pf->usdev_lock);

	kref_put(&pf->vf_cnt, usnic_ib_undiscover_pf);
	usnic_vnic_free(vf->vnic);
	pci_set_drvdata(pdev, NULL);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kfree(vf);

	usnic_info("Removed VF %s\n", pci_name(pdev));
}