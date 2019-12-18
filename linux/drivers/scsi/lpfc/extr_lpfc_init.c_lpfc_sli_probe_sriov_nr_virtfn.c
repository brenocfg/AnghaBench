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
typedef  int uint16_t ;
struct pci_dev {int dummy; } ;
struct lpfc_hba {struct pci_dev* pcidev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int lpfc_sli_sriov_nr_virtfn_get (struct lpfc_hba*) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 

int
lpfc_sli_probe_sriov_nr_virtfn(struct lpfc_hba *phba, int nr_vfn)
{
	struct pci_dev *pdev = phba->pcidev;
	uint16_t max_nr_vfn;
	int rc;

	max_nr_vfn = lpfc_sli_sriov_nr_virtfn_get(phba);
	if (nr_vfn > max_nr_vfn) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3057 Requested vfs (%d) greater than "
				"supported vfs (%d)", nr_vfn, max_nr_vfn);
		return -EINVAL;
	}

	rc = pci_enable_sriov(pdev, nr_vfn);
	if (rc) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
				"2806 Failed to enable sriov on this device "
				"with vfn number nr_vf:%d, rc:%d\n",
				nr_vfn, rc);
	} else
		lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
				"2807 Successful enable sriov on this device "
				"with vfn number nr_vf:%d\n", nr_vfn);
	return rc;
}