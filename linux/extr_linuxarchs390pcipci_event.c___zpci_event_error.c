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
struct zpci_dev {int /*<<< orphan*/  bus; } ;
struct zpci_ccdf_err {int /*<<< orphan*/  fid; int /*<<< orphan*/  pec; } ;
struct pci_dev {int /*<<< orphan*/  error_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZPCI_DEVFN ; 
 struct zpci_dev* get_zdev_by_fid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_err (char*) ; 
 int /*<<< orphan*/  zpci_err_hex (struct zpci_ccdf_err*,int) ; 

__attribute__((used)) static void __zpci_event_error(struct zpci_ccdf_err *ccdf)
{
	struct zpci_dev *zdev = get_zdev_by_fid(ccdf->fid);
	struct pci_dev *pdev = NULL;

	zpci_err("error CCDF:\n");
	zpci_err_hex(ccdf, sizeof(*ccdf));

	if (zdev)
		pdev = pci_get_slot(zdev->bus, ZPCI_DEVFN);

	pr_err("%s: Event 0x%x reports an error for PCI function 0x%x\n",
	       pdev ? pci_name(pdev) : "n/a", ccdf->pec, ccdf->fid);

	if (!pdev)
		return;

	pdev->error_state = pci_channel_io_perm_failure;
	pci_dev_put(pdev);
}