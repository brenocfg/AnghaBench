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
typedef  scalar_t__ u32 ;
struct brcmf_pcie_shared_info {scalar_t__ htod_mb_data_addr; } ;
struct brcmf_pciedev_info {int /*<<< orphan*/  pdev; int /*<<< orphan*/  ci; struct brcmf_pcie_shared_info shared; } ;
struct brcmf_core {int rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCIE2 ; 
 int /*<<< orphan*/  BRCMF_PCIE_REG_SBMBX ; 
 int EIO ; 
 int /*<<< orphan*/  PCIE ; 
 struct brcmf_core* brcmf_chip_get_core (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ brcmf_pcie_read_tcm32 (struct brcmf_pciedev_info*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_pcie_write_tcm32 (struct brcmf_pciedev_info*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
brcmf_pcie_send_mb_data(struct brcmf_pciedev_info *devinfo, u32 htod_mb_data)
{
	struct brcmf_pcie_shared_info *shared;
	struct brcmf_core *core;
	u32 addr;
	u32 cur_htod_mb_data;
	u32 i;

	shared = &devinfo->shared;
	addr = shared->htod_mb_data_addr;
	cur_htod_mb_data = brcmf_pcie_read_tcm32(devinfo, addr);

	if (cur_htod_mb_data != 0)
		brcmf_dbg(PCIE, "MB transaction is already pending 0x%04x\n",
			  cur_htod_mb_data);

	i = 0;
	while (cur_htod_mb_data != 0) {
		msleep(10);
		i++;
		if (i > 100)
			return -EIO;
		cur_htod_mb_data = brcmf_pcie_read_tcm32(devinfo, addr);
	}

	brcmf_pcie_write_tcm32(devinfo, addr, htod_mb_data);
	pci_write_config_dword(devinfo->pdev, BRCMF_PCIE_REG_SBMBX, 1);

	/* Send mailbox interrupt twice as a hardware workaround */
	core = brcmf_chip_get_core(devinfo->ci, BCMA_CORE_PCIE2);
	if (core->rev <= 13)
		pci_write_config_dword(devinfo->pdev, BRCMF_PCIE_REG_SBMBX, 1);

	return 0;
}