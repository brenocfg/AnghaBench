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
struct smsc9420_pdata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_CONTROL ; 
 int DMAC_CONTROL_SR_ ; 
 int /*<<< orphan*/  DMAC_INTR_ENA ; 
 int DMAC_INTR_ENA_RX_ ; 
 int /*<<< orphan*/  DMAC_STATUS ; 
 int DMAC_STS_RS_ ; 
 int DMAC_STS_RXPS_ ; 
 int /*<<< orphan*/  MAC_CR ; 
 int MAC_CR_RXEN_ ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  netif_warn (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  smsc9420_pci_flush_write (struct smsc9420_pdata*) ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void smsc9420_stop_rx(struct smsc9420_pdata *pd)
{
	int timeout = 1000;
	u32 mac_cr, dmac_control, dma_intr_ena;

	/* mask RX DMAC interrupts */
	dma_intr_ena = smsc9420_reg_read(pd, DMAC_INTR_ENA);
	dma_intr_ena &= (~DMAC_INTR_ENA_RX_);
	smsc9420_reg_write(pd, DMAC_INTR_ENA, dma_intr_ena);
	smsc9420_pci_flush_write(pd);

	/* stop RX MAC prior to stoping DMA */
	mac_cr = smsc9420_reg_read(pd, MAC_CR) & (~MAC_CR_RXEN_);
	smsc9420_reg_write(pd, MAC_CR, mac_cr);
	smsc9420_pci_flush_write(pd);

	/* stop RX DMAC */
	dmac_control = smsc9420_reg_read(pd, DMAC_CONTROL);
	dmac_control &= (~DMAC_CONTROL_SR_);
	smsc9420_reg_write(pd, DMAC_CONTROL, dmac_control);
	smsc9420_pci_flush_write(pd);

	/* wait up to 10ms for receive to stop */
	while (--timeout) {
		if (smsc9420_reg_read(pd, DMAC_STATUS) & DMAC_STS_RS_)
			break;
		udelay(10);
	}

	if (!timeout)
		netif_warn(pd, ifdown, pd->dev,
			   "RX DMAC did not stop! timeout\n");

	/* ACK the Rx DMAC stop bit */
	smsc9420_reg_write(pd, DMAC_STATUS, DMAC_STS_RXPS_);
}