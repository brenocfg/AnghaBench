#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct shdma_dev {TYPE_3__ dma_dev; } ;
struct sudmac_device {TYPE_2__* pdata; int /*<<< orphan*/  chan_reg; struct shdma_dev shdma_dev; } ;
struct shdma_chan {int max_xfer_len; } ;
struct sudmac_chan {int cfg; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  dint_end_bit; int /*<<< orphan*/  offset; int /*<<< orphan*/  base; struct shdma_chan shdma_chan; } ;
struct platform_device {scalar_t__ id; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* channel; } ;
struct TYPE_4__ {int config; int wait; int dint_end_bit; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SUDMAC_CH0ENDE ; 
 int /*<<< orphan*/  SUDMAC_CH1ENDE ; 
 int SUDMAC_DMA_BIT_CH0 ; 
 int SUDMAC_DMA_BIT_CH1 ; 
 int SUDMAC_LBA_WAIT ; 
 int SUDMAC_RCVENDM ; 
 int SUDMAC_RX_END_MODE ; 
 int SUDMAC_SENDBUFM ; 
 int SUDMAC_TX_BUFFER_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 struct sudmac_chan* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shdma_chan_probe (struct shdma_dev*,struct shdma_chan*,int) ; 
 int /*<<< orphan*/  shdma_chan_remove (struct shdma_chan*) ; 
 int shdma_request_irq (struct shdma_chan*,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,...) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sudmac_chan_probe(struct sudmac_device *su_dev, int id, int irq,
			     unsigned long flags)
{
	struct shdma_dev *sdev = &su_dev->shdma_dev;
	struct platform_device *pdev = to_platform_device(sdev->dma_dev.dev);
	struct sudmac_chan *sc;
	struct shdma_chan *schan;
	int err;

	sc = devm_kzalloc(&pdev->dev, sizeof(struct sudmac_chan), GFP_KERNEL);
	if (!sc)
		return -ENOMEM;

	schan = &sc->shdma_chan;
	schan->max_xfer_len = 64 * 1024 * 1024 - 1;

	shdma_chan_probe(sdev, schan, id);

	sc->base = su_dev->chan_reg;

	/* get platform_data */
	sc->offset = su_dev->pdata->channel->offset;
	if (su_dev->pdata->channel->config & SUDMAC_TX_BUFFER_MODE)
		sc->cfg |= SUDMAC_SENDBUFM;
	if (su_dev->pdata->channel->config & SUDMAC_RX_END_MODE)
		sc->cfg |= SUDMAC_RCVENDM;
	sc->cfg |= (su_dev->pdata->channel->wait << 4) & SUDMAC_LBA_WAIT;

	if (su_dev->pdata->channel->dint_end_bit & SUDMAC_DMA_BIT_CH0)
		sc->dint_end_bit |= SUDMAC_CH0ENDE;
	if (su_dev->pdata->channel->dint_end_bit & SUDMAC_DMA_BIT_CH1)
		sc->dint_end_bit |= SUDMAC_CH1ENDE;

	/* set up channel irq */
	if (pdev->id >= 0)
		snprintf(sc->dev_id, sizeof(sc->dev_id), "sudmac%d.%d",
			 pdev->id, id);
	else
		snprintf(sc->dev_id, sizeof(sc->dev_id), "sudmac%d", id);

	err = shdma_request_irq(schan, irq, flags, sc->dev_id);
	if (err) {
		dev_err(sdev->dma_dev.dev,
			"DMA channel %d request_irq failed %d\n", id, err);
		goto err_no_irq;
	}

	return 0;

err_no_irq:
	/* remove from dmaengine device node */
	shdma_chan_remove(schan);
	return err;
}