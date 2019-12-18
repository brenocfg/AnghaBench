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
struct imx7_csi {int buf_num; int last_eof; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  last_eof_completion; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT_ADDR_CH_ERR_INT ; 
 int BIT_DMA_TSF_DONE_FB1 ; 
 int BIT_DMA_TSF_DONE_FB2 ; 
 int BIT_HRESP_ERR_INT ; 
 int BIT_RFF_OR_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  imx7_csi_dma_reflash (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_error_recovery (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_hw_disable (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_hw_enable (struct imx7_csi*) ; 
 int imx7_csi_irq_clear (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_vb2_buf_done (struct imx7_csi*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t imx7_csi_irq_handler(int irq, void *data)
{
	struct imx7_csi *csi =  data;
	u32 status;

	spin_lock(&csi->irqlock);

	status = imx7_csi_irq_clear(csi);

	if (status & BIT_RFF_OR_INT) {
		dev_warn(csi->dev, "Rx fifo overflow\n");
		imx7_csi_error_recovery(csi);
	}

	if (status & BIT_HRESP_ERR_INT) {
		dev_warn(csi->dev, "Hresponse error detected\n");
		imx7_csi_error_recovery(csi);
	}

	if (status & BIT_ADDR_CH_ERR_INT) {
		imx7_csi_hw_disable(csi);

		imx7_csi_dma_reflash(csi);

		imx7_csi_hw_enable(csi);
	}

	if ((status & BIT_DMA_TSF_DONE_FB1) &&
	    (status & BIT_DMA_TSF_DONE_FB2)) {
		/*
		 * For both FB1 and FB2 interrupter bits set case,
		 * CSI DMA is work in one of FB1 and FB2 buffer,
		 * but software can not know the state.
		 * Skip it to avoid base address updated
		 * when csi work in field0 and field1 will write to
		 * new base address.
		 */
	} else if (status & BIT_DMA_TSF_DONE_FB1) {
		csi->buf_num = 0;
	} else if (status & BIT_DMA_TSF_DONE_FB2) {
		csi->buf_num = 1;
	}

	if ((status & BIT_DMA_TSF_DONE_FB1) ||
	    (status & BIT_DMA_TSF_DONE_FB2)) {
		imx7_csi_vb2_buf_done(csi);

		if (csi->last_eof) {
			complete(&csi->last_eof_completion);
			csi->last_eof = false;
		}
	}

	spin_unlock(&csi->irqlock);

	return IRQ_HANDLED;
}