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
struct brcmf_pciedev_info {int in_irq; scalar_t__ state; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BRCMFMAC_PCIE_STATE_UP ; 
 int BRCMF_PCIE_MB_INT_D2H_DB ; 
 int BRCMF_PCIE_MB_INT_FN0_0 ; 
 int BRCMF_PCIE_MB_INT_FN0_1 ; 
 int /*<<< orphan*/  BRCMF_PCIE_PCIE2REG_MAILBOXINT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  brcmf_pcie_bus_console_read (struct brcmf_pciedev_info*,int) ; 
 int /*<<< orphan*/  brcmf_pcie_handle_mb_data (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_intr_enable (struct brcmf_pciedev_info*) ; 
 int brcmf_pcie_read_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_write_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcmf_proto_msgbuf_rx_trigger (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t brcmf_pcie_isr_thread(int irq, void *arg)
{
	struct brcmf_pciedev_info *devinfo = (struct brcmf_pciedev_info *)arg;
	u32 status;

	devinfo->in_irq = true;
	status = brcmf_pcie_read_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT);
	brcmf_dbg(PCIE, "Enter %x\n", status);
	if (status) {
		brcmf_pcie_write_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT,
				       status);
		if (status & (BRCMF_PCIE_MB_INT_FN0_0 |
			      BRCMF_PCIE_MB_INT_FN0_1))
			brcmf_pcie_handle_mb_data(devinfo);
		if (status & BRCMF_PCIE_MB_INT_D2H_DB) {
			if (devinfo->state == BRCMFMAC_PCIE_STATE_UP)
				brcmf_proto_msgbuf_rx_trigger(
							&devinfo->pdev->dev);
		}
	}
	brcmf_pcie_bus_console_read(devinfo, false);
	if (devinfo->state == BRCMFMAC_PCIE_STATE_UP)
		brcmf_pcie_intr_enable(devinfo);
	devinfo->in_irq = false;
	return IRQ_HANDLED;
}