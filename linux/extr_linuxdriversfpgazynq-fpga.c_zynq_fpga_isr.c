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
struct zynq_fpga_priv {int /*<<< orphan*/  dma_done; int /*<<< orphan*/  dma_lock; scalar_t__ cur_sg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_STS_OFFSET ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int IXR_DMA_DONE_MASK ; 
 int IXR_ERROR_FLAGS_MASK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int zynq_fpga_read (struct zynq_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_fpga_set_irq (struct zynq_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_fpga_write (struct zynq_fpga_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zynq_step_dma (struct zynq_fpga_priv*) ; 

__attribute__((used)) static irqreturn_t zynq_fpga_isr(int irq, void *data)
{
	struct zynq_fpga_priv *priv = data;
	u32 intr_status;

	/* If anything other than DMA completion is reported stop and hand
	 * control back to zynq_fpga_ops_write, something went wrong,
	 * otherwise progress the DMA.
	 */
	spin_lock(&priv->dma_lock);
	intr_status = zynq_fpga_read(priv, INT_STS_OFFSET);
	if (!(intr_status & IXR_ERROR_FLAGS_MASK) &&
	    (intr_status & IXR_DMA_DONE_MASK) && priv->cur_sg) {
		zynq_fpga_write(priv, INT_STS_OFFSET, IXR_DMA_DONE_MASK);
		zynq_step_dma(priv);
		spin_unlock(&priv->dma_lock);
		return IRQ_HANDLED;
	}
	spin_unlock(&priv->dma_lock);

	zynq_fpga_set_irq(priv, 0);
	complete(&priv->dma_done);

	return IRQ_HANDLED;
}