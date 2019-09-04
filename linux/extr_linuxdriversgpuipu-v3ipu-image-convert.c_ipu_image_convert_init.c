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
struct ipu_soc {struct ipu_image_convert_priv* image_convert_priv; } ;
struct ipu_image_convert_priv {struct ipu_image_convert_chan* chan; struct ipu_soc* ipu; } ;
struct ipu_image_convert_chan {int ic_task; int out_eof_irq; int rot_out_eof_irq; int /*<<< orphan*/  done_q; int /*<<< orphan*/  pending_q; int /*<<< orphan*/  ctx_list; int /*<<< orphan*/  irqlock; int /*<<< orphan*/ * dma_ch; struct ipu_image_convert_priv* priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IC_NUM_TASKS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ipu_image_convert_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * image_convert_dma_chan ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ipu_image_convert_init(struct ipu_soc *ipu, struct device *dev)
{
	struct ipu_image_convert_priv *priv;
	int i;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ipu->image_convert_priv = priv;
	priv->ipu = ipu;

	for (i = 0; i < IC_NUM_TASKS; i++) {
		struct ipu_image_convert_chan *chan = &priv->chan[i];

		chan->ic_task = i;
		chan->priv = priv;
		chan->dma_ch = &image_convert_dma_chan[i];
		chan->out_eof_irq = -1;
		chan->rot_out_eof_irq = -1;

		spin_lock_init(&chan->irqlock);
		INIT_LIST_HEAD(&chan->ctx_list);
		INIT_LIST_HEAD(&chan->pending_q);
		INIT_LIST_HEAD(&chan->done_q);
	}

	return 0;
}