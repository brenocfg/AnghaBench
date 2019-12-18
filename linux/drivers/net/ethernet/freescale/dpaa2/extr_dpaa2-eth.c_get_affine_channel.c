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
struct dpaa2_eth_priv {int num_channels; struct dpaa2_eth_channel** channel; TYPE_2__* net_dev; } ;
struct TYPE_6__ {int desired_cpu; } ;
struct dpaa2_eth_channel {TYPE_3__ nctx; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 

__attribute__((used)) static struct dpaa2_eth_channel *get_affine_channel(struct dpaa2_eth_priv *priv,
						    int cpu)
{
	struct device *dev = priv->net_dev->dev.parent;
	int i;

	for (i = 0; i < priv->num_channels; i++)
		if (priv->channel[i]->nctx.desired_cpu == cpu)
			return priv->channel[i];

	/* We should never get here. Issue a warning and return
	 * the first channel, because it's still better than nothing
	 */
	dev_warn(dev, "No affine channel found for cpu %d\n", cpu);

	return priv->channel[0];
}