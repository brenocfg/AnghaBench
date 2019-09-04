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
struct mtk_dsi {int /*<<< orphan*/  irq_wait_queue; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CMD_DONE_INT_FLAG ; 
 int DSI_BUSY ; 
 scalar_t__ DSI_INTSTA ; 
 scalar_t__ DSI_RACK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int LPRX_RD_RDY_INT_FLAG ; 
 int RACK ; 
 int VM_DONE_INT_FLAG ; 
 int /*<<< orphan*/  mtk_dsi_irq_data_set (struct mtk_dsi*,int) ; 
 int /*<<< orphan*/  mtk_dsi_mask (struct mtk_dsi*,scalar_t__,int,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mtk_dsi_irq(int irq, void *dev_id)
{
	struct mtk_dsi *dsi = dev_id;
	u32 status, tmp;
	u32 flag = LPRX_RD_RDY_INT_FLAG | CMD_DONE_INT_FLAG | VM_DONE_INT_FLAG;

	status = readl(dsi->regs + DSI_INTSTA) & flag;

	if (status) {
		do {
			mtk_dsi_mask(dsi, DSI_RACK, RACK, RACK);
			tmp = readl(dsi->regs + DSI_INTSTA);
		} while (tmp & DSI_BUSY);

		mtk_dsi_mask(dsi, DSI_INTSTA, status, 0);
		mtk_dsi_irq_data_set(dsi, status);
		wake_up_interruptible(&dsi->irq_wait_queue);
	}

	return IRQ_HANDLED;
}