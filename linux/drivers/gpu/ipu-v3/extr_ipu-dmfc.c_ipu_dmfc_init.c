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
struct ipu_soc {struct ipu_dmfc_priv* dmfc_priv; } ;
struct ipu_dmfc_priv {scalar_t__ base; TYPE_1__* channels; int /*<<< orphan*/  mutex; struct ipu_soc* ipu; struct device* dev; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {scalar_t__ ipu_channel; } ;
struct TYPE_3__ {int slots; TYPE_2__* data; struct ipu_soc* ipu; struct ipu_dmfc_priv* priv; } ;

/* Variables and functions */
 scalar_t__ DMFC_DP_CHAN ; 
 scalar_t__ DMFC_DP_CHAN_DEF ; 
 scalar_t__ DMFC_GENERAL1 ; 
 int DMFC_NUM_CHANNELS ; 
 scalar_t__ DMFC_WR_CHAN ; 
 scalar_t__ DMFC_WR_CHAN_DEF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IPUV3_CHANNEL_MEM_BG_SYNC ; 
 scalar_t__ IPUV3_CHANNEL_MEM_DC_SYNC ; 
 scalar_t__ IPUV3_CHANNEL_MEM_FG_SYNC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ devm_ioremap (struct device*,unsigned long,int /*<<< orphan*/ ) ; 
 struct ipu_dmfc_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* dmfcdata ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int ipu_dmfc_init(struct ipu_soc *ipu, struct device *dev, unsigned long base,
		struct clk *ipu_clk)
{
	struct ipu_dmfc_priv *priv;
	int i;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->base = devm_ioremap(dev, base, PAGE_SIZE);
	if (!priv->base)
		return -ENOMEM;

	priv->dev = dev;
	priv->ipu = ipu;
	mutex_init(&priv->mutex);

	ipu->dmfc_priv = priv;

	for (i = 0; i < DMFC_NUM_CHANNELS; i++) {
		priv->channels[i].priv = priv;
		priv->channels[i].ipu = ipu;
		priv->channels[i].data = &dmfcdata[i];

		if (dmfcdata[i].ipu_channel == IPUV3_CHANNEL_MEM_BG_SYNC ||
		    dmfcdata[i].ipu_channel == IPUV3_CHANNEL_MEM_FG_SYNC ||
		    dmfcdata[i].ipu_channel == IPUV3_CHANNEL_MEM_DC_SYNC)
			priv->channels[i].slots = 2;
	}

	writel(0x00000050, priv->base + DMFC_WR_CHAN);
	writel(0x00005654, priv->base + DMFC_DP_CHAN);
	writel(0x202020f6, priv->base + DMFC_WR_CHAN_DEF);
	writel(0x2020f6f6, priv->base + DMFC_DP_CHAN_DEF);
	writel(0x00000003, priv->base + DMFC_GENERAL1);

	return 0;
}