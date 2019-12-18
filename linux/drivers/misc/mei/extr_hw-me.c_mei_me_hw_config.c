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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct mei_me_hw {int hbuf_depth; int d0i3_supported; int /*<<< orphan*/  pg_state; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int H_CBD ; 
 int H_D0I3C_I3 ; 
 int /*<<< orphan*/  MEI_PG_OFF ; 
 int /*<<< orphan*/  MEI_PG_ON ; 
 int /*<<< orphan*/  PCI_CFG_HFS_1 ; 
 int PCI_CFG_HFS_1_D0I3_MSK ; 
 int mei_hcsr_read (struct mei_device*) ; 
 int mei_me_d0i3c_read (struct mei_device*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mei_pci_cfg_read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mei_me_hw_config(struct mei_device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev->dev);
	struct mei_me_hw *hw = to_me_hw(dev);
	u32 hcsr, reg;

	/* Doesn't change in runtime */
	hcsr = mei_hcsr_read(dev);
	hw->hbuf_depth = (hcsr & H_CBD) >> 24;

	reg = 0;
	pci_read_config_dword(pdev, PCI_CFG_HFS_1, &reg);
	trace_mei_pci_cfg_read(dev->dev, "PCI_CFG_HFS_1", PCI_CFG_HFS_1, reg);
	hw->d0i3_supported =
		((reg & PCI_CFG_HFS_1_D0I3_MSK) == PCI_CFG_HFS_1_D0I3_MSK);

	hw->pg_state = MEI_PG_OFF;
	if (hw->d0i3_supported) {
		reg = mei_me_d0i3c_read(dev);
		if (reg & H_D0I3C_I3)
			hw->pg_state = MEI_PG_ON;
	}
}