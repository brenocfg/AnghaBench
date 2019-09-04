#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipu_image_convert_priv {TYPE_1__* ipu; } ;
struct ipu_image_convert_dma_chan {int /*<<< orphan*/  rot_out; int /*<<< orphan*/  rot_in; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct ipu_image_convert_chan {int out_eof_irq; int rot_out_eof_irq; void* rotation_out_chan; void* out_chan; void* rotation_in_chan; void* in_chan; void* ic; int /*<<< orphan*/  ic_task; struct ipu_image_convert_priv* priv; struct ipu_image_convert_dma_chan* dma_ch; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IPU_IRQ_EOF ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_bh ; 
 void* ipu_ic_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* ipu_idmac_channel_irq (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 void* ipu_idmac_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  norotate_irq ; 
 int /*<<< orphan*/  release_ipu_resources (struct ipu_image_convert_chan*) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ipu_image_convert_chan*) ; 
 int /*<<< orphan*/  rotate_irq ; 

__attribute__((used)) static int get_ipu_resources(struct ipu_image_convert_chan *chan)
{
	const struct ipu_image_convert_dma_chan *dma = chan->dma_ch;
	struct ipu_image_convert_priv *priv = chan->priv;
	int ret;

	/* get IC */
	chan->ic = ipu_ic_get(priv->ipu, chan->ic_task);
	if (IS_ERR(chan->ic)) {
		dev_err(priv->ipu->dev, "could not acquire IC\n");
		ret = PTR_ERR(chan->ic);
		goto err;
	}

	/* get IDMAC channels */
	chan->in_chan = ipu_idmac_get(priv->ipu, dma->in);
	chan->out_chan = ipu_idmac_get(priv->ipu, dma->out);
	if (IS_ERR(chan->in_chan) || IS_ERR(chan->out_chan)) {
		dev_err(priv->ipu->dev, "could not acquire idmac channels\n");
		ret = -EBUSY;
		goto err;
	}

	chan->rotation_in_chan = ipu_idmac_get(priv->ipu, dma->rot_in);
	chan->rotation_out_chan = ipu_idmac_get(priv->ipu, dma->rot_out);
	if (IS_ERR(chan->rotation_in_chan) || IS_ERR(chan->rotation_out_chan)) {
		dev_err(priv->ipu->dev,
			"could not acquire idmac rotation channels\n");
		ret = -EBUSY;
		goto err;
	}

	/* acquire the EOF interrupts */
	chan->out_eof_irq = ipu_idmac_channel_irq(priv->ipu,
						  chan->out_chan,
						  IPU_IRQ_EOF);

	ret = request_threaded_irq(chan->out_eof_irq, norotate_irq, do_bh,
				   0, "ipu-ic", chan);
	if (ret < 0) {
		dev_err(priv->ipu->dev, "could not acquire irq %d\n",
			 chan->out_eof_irq);
		chan->out_eof_irq = -1;
		goto err;
	}

	chan->rot_out_eof_irq = ipu_idmac_channel_irq(priv->ipu,
						     chan->rotation_out_chan,
						     IPU_IRQ_EOF);

	ret = request_threaded_irq(chan->rot_out_eof_irq, rotate_irq, do_bh,
				   0, "ipu-ic", chan);
	if (ret < 0) {
		dev_err(priv->ipu->dev, "could not acquire irq %d\n",
			chan->rot_out_eof_irq);
		chan->rot_out_eof_irq = -1;
		goto err;
	}

	return 0;
err:
	release_ipu_resources(chan);
	return ret;
}