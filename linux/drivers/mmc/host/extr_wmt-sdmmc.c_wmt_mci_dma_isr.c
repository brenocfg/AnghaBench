#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wmt_mci_priv {scalar_t__ comp_cmd; int /*<<< orphan*/  comp_dma; TYPE_2__* req; int /*<<< orphan*/  dev; scalar_t__ sdmmc_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int DMA_CCR_EVT_SUCCESS ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SDDMA_CCR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 scalar_t__ completion_done (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wmt_complete_data_request (struct wmt_mci_priv*) ; 
 int /*<<< orphan*/  wmt_mci_disable_dma (struct wmt_mci_priv*) ; 

__attribute__((used)) static irqreturn_t wmt_mci_dma_isr(int irq_num, void *data)
{
	struct wmt_mci_priv *priv;

	int status;

	priv = (struct wmt_mci_priv *)data;

	status = readl(priv->sdmmc_base + SDDMA_CCR) & 0x0F;

	if (status != DMA_CCR_EVT_SUCCESS) {
		dev_err(priv->dev, "DMA Error: Status = %d\n", status);
		priv->req->data->error = -ETIMEDOUT;
		complete(priv->comp_dma);
		return IRQ_HANDLED;
	}

	priv->req->data->error = 0;

	wmt_mci_disable_dma(priv);

	complete(priv->comp_dma);

	if (priv->comp_cmd) {
		if (completion_done(priv->comp_cmd)) {
			/*
			 * if the command (regular) interrupt has already
			 * completed, finish off the request otherwise we wait
			 * for the command interrupt and finish from there.
			 */
			wmt_complete_data_request(priv);
		}
	}

	return IRQ_HANDLED;
}