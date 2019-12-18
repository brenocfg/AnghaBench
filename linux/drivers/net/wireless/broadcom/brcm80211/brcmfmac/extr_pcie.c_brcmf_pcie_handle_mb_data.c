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
typedef  int u32 ;
struct brcmf_pcie_shared_info {int dtoh_mb_data_addr; } ;
struct brcmf_pciedev_info {int mbdata_completed; TYPE_1__* pdev; int /*<<< orphan*/  mbdata_resp_wait; struct brcmf_pcie_shared_info shared; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BRCMF_D2H_DEV_D3_ACK ; 
 int BRCMF_D2H_DEV_DS_ENTER_REQ ; 
 int BRCMF_D2H_DEV_DS_EXIT_NOTE ; 
 int BRCMF_D2H_DEV_FWHALT ; 
 int /*<<< orphan*/  BRCMF_H2D_HOST_DS_ACK ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_fw_crashed (int /*<<< orphan*/ *) ; 
 int brcmf_pcie_read_tcm32 (struct brcmf_pciedev_info*,int) ; 
 int /*<<< orphan*/  brcmf_pcie_send_mb_data (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_write_tcm32 (struct brcmf_pciedev_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_pcie_handle_mb_data(struct brcmf_pciedev_info *devinfo)
{
	struct brcmf_pcie_shared_info *shared;
	u32 addr;
	u32 dtoh_mb_data;

	shared = &devinfo->shared;
	addr = shared->dtoh_mb_data_addr;
	dtoh_mb_data = brcmf_pcie_read_tcm32(devinfo, addr);

	if (!dtoh_mb_data)
		return;

	brcmf_pcie_write_tcm32(devinfo, addr, 0);

	brcmf_dbg(PCIE, "D2H_MB_DATA: 0x%04x\n", dtoh_mb_data);
	if (dtoh_mb_data & BRCMF_D2H_DEV_DS_ENTER_REQ)  {
		brcmf_dbg(PCIE, "D2H_MB_DATA: DEEP SLEEP REQ\n");
		brcmf_pcie_send_mb_data(devinfo, BRCMF_H2D_HOST_DS_ACK);
		brcmf_dbg(PCIE, "D2H_MB_DATA: sent DEEP SLEEP ACK\n");
	}
	if (dtoh_mb_data & BRCMF_D2H_DEV_DS_EXIT_NOTE)
		brcmf_dbg(PCIE, "D2H_MB_DATA: DEEP SLEEP EXIT\n");
	if (dtoh_mb_data & BRCMF_D2H_DEV_D3_ACK) {
		brcmf_dbg(PCIE, "D2H_MB_DATA: D3 ACK\n");
		devinfo->mbdata_completed = true;
		wake_up(&devinfo->mbdata_resp_wait);
	}
	if (dtoh_mb_data & BRCMF_D2H_DEV_FWHALT) {
		brcmf_dbg(PCIE, "D2H_MB_DATA: FW HALT\n");
		brcmf_fw_crashed(&devinfo->pdev->dev);
	}
}