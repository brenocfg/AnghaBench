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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct smi_port {int* dma_addr; int /*<<< orphan*/  DMA_CHAN1_CONTROL; int /*<<< orphan*/  DMA_CHAN1_ADDR_HI; int /*<<< orphan*/  DMA_CHAN1_ADDR_LOW; scalar_t__ _dmaInterruptCH1; int /*<<< orphan*/  DMA_CHAN0_CONTROL; int /*<<< orphan*/  DMA_CHAN0_ADDR_HI; int /*<<< orphan*/  DMA_CHAN0_ADDR_LOW; scalar_t__ _dmaInterruptCH0; int /*<<< orphan*/  DMA_MANAGEMENT; struct smi_dev* dev; } ;
struct smi_dev {int dummy; } ;

/* Variables and functions */
 int DMA_TRANS_UNIT_188 ; 
 int SMI_TS_DMA_BUF_SIZE ; 
 int smi_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 smi_config_DMA(struct smi_port *port)
{
	struct smi_dev *dev = port->dev;
	u32 totalLength = 0, dmaMemPtrLow, dmaMemPtrHi, dmaCtlReg;
	u8 chanLatencyTimer = 0, dmaChanEnable = 1, dmaTransStart = 1;
	u32 dmaManagement = 0, tlpTransUnit = DMA_TRANS_UNIT_188;
	u8 tlpTc = 0, tlpTd = 1, tlpEp = 0, tlpAttr = 0;
	u64 mem;

	dmaManagement = smi_read(port->DMA_MANAGEMENT);
	/* Setup Channel-0 */
	if (port->_dmaInterruptCH0) {
		totalLength = SMI_TS_DMA_BUF_SIZE;
		mem = port->dma_addr[0];
		dmaMemPtrLow = mem & 0xffffffff;
		dmaMemPtrHi = mem >> 32;
		dmaCtlReg = (totalLength) | (tlpTransUnit << 22) | (tlpTc << 25)
			| (tlpTd << 28) | (tlpEp << 29) | (tlpAttr << 30);
		dmaManagement |= dmaChanEnable | (dmaTransStart << 1)
			| (chanLatencyTimer << 8);
		/* write DMA register, start DMA engine */
		smi_write(port->DMA_CHAN0_ADDR_LOW, dmaMemPtrLow);
		smi_write(port->DMA_CHAN0_ADDR_HI, dmaMemPtrHi);
		smi_write(port->DMA_CHAN0_CONTROL, dmaCtlReg);
	}
	/* Setup Channel-1 */
	if (port->_dmaInterruptCH1) {
		totalLength = SMI_TS_DMA_BUF_SIZE;
		mem = port->dma_addr[1];
		dmaMemPtrLow = mem & 0xffffffff;
		dmaMemPtrHi = mem >> 32;
		dmaCtlReg = (totalLength) | (tlpTransUnit << 22) | (tlpTc << 25)
			| (tlpTd << 28) | (tlpEp << 29) | (tlpAttr << 30);
		dmaManagement |= (dmaChanEnable << 16) | (dmaTransStart << 17)
			| (chanLatencyTimer << 24);
		/* write DMA register, start DMA engine */
		smi_write(port->DMA_CHAN1_ADDR_LOW, dmaMemPtrLow);
		smi_write(port->DMA_CHAN1_ADDR_HI, dmaMemPtrHi);
		smi_write(port->DMA_CHAN1_CONTROL, dmaCtlReg);
	}
	return dmaManagement;
}