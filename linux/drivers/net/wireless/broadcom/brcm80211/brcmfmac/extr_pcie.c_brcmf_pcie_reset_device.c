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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct brcmf_pciedev_info {int /*<<< orphan*/  ci; int /*<<< orphan*/  pdev; } ;
struct brcmf_core {int rev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 int /*<<< orphan*/  BCMA_CORE_CHIPCOMMON ; 
 int /*<<< orphan*/  BCMA_CORE_PCIE2 ; 
 size_t BRCMF_PCIE_CFGREG_LINK_STATUS_CTRL2 ; 
 size_t BRCMF_PCIE_CFGREG_MSI_ADDR_H ; 
 size_t BRCMF_PCIE_CFGREG_MSI_ADDR_L ; 
 size_t BRCMF_PCIE_CFGREG_MSI_CAP ; 
 size_t BRCMF_PCIE_CFGREG_MSI_DATA ; 
 size_t BRCMF_PCIE_CFGREG_PML1_SUB_CTRL1 ; 
 size_t BRCMF_PCIE_CFGREG_PM_CSR ; 
 size_t BRCMF_PCIE_CFGREG_RBAR_CTRL ; 
 size_t BRCMF_PCIE_CFGREG_REG_BAR2_CONFIG ; 
 size_t BRCMF_PCIE_CFGREG_REG_BAR3_CONFIG ; 
 size_t BRCMF_PCIE_CFGREG_STATUS_CMD ; 
 size_t BRCMF_PCIE_LINK_STATUS_CTRL_ASPM_ENAB ; 
 int /*<<< orphan*/  BRCMF_PCIE_PCIE2REG_CONFIGADDR ; 
 int /*<<< orphan*/  BRCMF_PCIE_PCIE2REG_CONFIGDATA ; 
 int /*<<< orphan*/  BRCMF_PCIE_REG_LINK_STATUS_CTRL ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  WRITECC32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,int) ; 
 struct brcmf_core* brcmf_chip_get_core (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 size_t brcmf_pcie_read_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_select_core (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_write_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  watchdog ; 

__attribute__((used)) static void brcmf_pcie_reset_device(struct brcmf_pciedev_info *devinfo)
{
	struct brcmf_core *core;
	u16 cfg_offset[] = { BRCMF_PCIE_CFGREG_STATUS_CMD,
			     BRCMF_PCIE_CFGREG_PM_CSR,
			     BRCMF_PCIE_CFGREG_MSI_CAP,
			     BRCMF_PCIE_CFGREG_MSI_ADDR_L,
			     BRCMF_PCIE_CFGREG_MSI_ADDR_H,
			     BRCMF_PCIE_CFGREG_MSI_DATA,
			     BRCMF_PCIE_CFGREG_LINK_STATUS_CTRL2,
			     BRCMF_PCIE_CFGREG_RBAR_CTRL,
			     BRCMF_PCIE_CFGREG_PML1_SUB_CTRL1,
			     BRCMF_PCIE_CFGREG_REG_BAR2_CONFIG,
			     BRCMF_PCIE_CFGREG_REG_BAR3_CONFIG };
	u32 i;
	u32 val;
	u32 lsc;

	if (!devinfo->ci)
		return;

	/* Disable ASPM */
	brcmf_pcie_select_core(devinfo, BCMA_CORE_PCIE2);
	pci_read_config_dword(devinfo->pdev, BRCMF_PCIE_REG_LINK_STATUS_CTRL,
			      &lsc);
	val = lsc & (~BRCMF_PCIE_LINK_STATUS_CTRL_ASPM_ENAB);
	pci_write_config_dword(devinfo->pdev, BRCMF_PCIE_REG_LINK_STATUS_CTRL,
			       val);

	/* Watchdog reset */
	brcmf_pcie_select_core(devinfo, BCMA_CORE_CHIPCOMMON);
	WRITECC32(devinfo, watchdog, 4);
	msleep(100);

	/* Restore ASPM */
	brcmf_pcie_select_core(devinfo, BCMA_CORE_PCIE2);
	pci_write_config_dword(devinfo->pdev, BRCMF_PCIE_REG_LINK_STATUS_CTRL,
			       lsc);

	core = brcmf_chip_get_core(devinfo->ci, BCMA_CORE_PCIE2);
	if (core->rev <= 13) {
		for (i = 0; i < ARRAY_SIZE(cfg_offset); i++) {
			brcmf_pcie_write_reg32(devinfo,
					       BRCMF_PCIE_PCIE2REG_CONFIGADDR,
					       cfg_offset[i]);
			val = brcmf_pcie_read_reg32(devinfo,
				BRCMF_PCIE_PCIE2REG_CONFIGDATA);
			brcmf_dbg(PCIE, "config offset 0x%04x, value 0x%04x\n",
				  cfg_offset[i], val);
			brcmf_pcie_write_reg32(devinfo,
					       BRCMF_PCIE_PCIE2REG_CONFIGDATA,
					       val);
		}
	}
}