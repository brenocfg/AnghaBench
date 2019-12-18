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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct intel_th {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_TH_CAP (struct intel_th*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPKDSC_TSACT ; 
 int /*<<< orphan*/  PCI_REG_NPKDSC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscu_enable ; 

__attribute__((used)) static int intel_th_pci_activate(struct intel_th *th)
{
	struct pci_dev *pdev = to_pci_dev(th->dev);
	u32 npkdsc;
	int err;

	if (!INTEL_TH_CAP(th, tscu_enable))
		return 0;

	err = pci_read_config_dword(pdev, PCI_REG_NPKDSC, &npkdsc);
	if (!err) {
		npkdsc |= NPKDSC_TSACT;
		err = pci_write_config_dword(pdev, PCI_REG_NPKDSC, npkdsc);
	}

	if (err)
		dev_err(&pdev->dev, "failed to read NPKDSC register\n");

	return err;
}