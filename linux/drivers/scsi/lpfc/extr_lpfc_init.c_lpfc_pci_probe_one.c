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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct lpfc_sli_intf {int /*<<< orphan*/  word0; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  LPFC_SLI_INTF ; 
 scalar_t__ LPFC_SLI_INTF_REV_SLI4 ; 
 scalar_t__ LPFC_SLI_INTF_VALID ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct lpfc_sli_intf*) ; 
 int lpfc_pci_probe_one_s3 (struct pci_dev*,struct pci_device_id const*) ; 
 int lpfc_pci_probe_one_s4 (struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  lpfc_sli_intf_slirev ; 
 int /*<<< orphan*/  lpfc_sli_intf_valid ; 
 scalar_t__ pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_pci_probe_one(struct pci_dev *pdev, const struct pci_device_id *pid)
{
	int rc;
	struct lpfc_sli_intf intf;

	if (pci_read_config_dword(pdev, LPFC_SLI_INTF, &intf.word0))
		return -ENODEV;

	if ((bf_get(lpfc_sli_intf_valid, &intf) == LPFC_SLI_INTF_VALID) &&
	    (bf_get(lpfc_sli_intf_slirev, &intf) == LPFC_SLI_INTF_REV_SLI4))
		rc = lpfc_pci_probe_one_s4(pdev, pid);
	else
		rc = lpfc_pci_probe_one_s3(pdev, pid);

	return rc;
}