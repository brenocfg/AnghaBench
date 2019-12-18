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
struct ipu_soc {struct ipu_dp_priv* dp_priv; } ;
struct ipu_dp_priv {TYPE_3__* flow; scalar_t__ base; int /*<<< orphan*/  mutex; struct ipu_soc* ipu; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int foreground; void* in_cs; } ;
struct TYPE_4__ {void* in_cs; } ;
struct TYPE_6__ {struct ipu_dp_priv* priv; scalar_t__ base; TYPE_2__ foreground; TYPE_1__ background; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* IPUV3_COLORSPACE_UNKNOWN ; 
 int IPUV3_NUM_FLOWS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ devm_ioremap (struct device*,unsigned long,int /*<<< orphan*/ ) ; 
 struct ipu_dp_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__* ipu_dp_flow_base ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int ipu_dp_init(struct ipu_soc *ipu, struct device *dev, unsigned long base)
{
	struct ipu_dp_priv *priv;
	int i;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	priv->dev = dev;
	priv->ipu = ipu;

	ipu->dp_priv = priv;

	priv->base = devm_ioremap(dev, base, PAGE_SIZE);
	if (!priv->base)
		return -ENOMEM;

	mutex_init(&priv->mutex);

	for (i = 0; i < IPUV3_NUM_FLOWS; i++) {
		priv->flow[i].background.in_cs = IPUV3_COLORSPACE_UNKNOWN;
		priv->flow[i].foreground.in_cs = IPUV3_COLORSPACE_UNKNOWN;
		priv->flow[i].foreground.foreground = true;
		priv->flow[i].base = priv->base + ipu_dp_flow_base[i];
		priv->flow[i].priv = priv;
	}

	return 0;
}