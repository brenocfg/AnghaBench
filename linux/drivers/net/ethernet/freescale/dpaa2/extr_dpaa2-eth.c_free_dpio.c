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
struct dpaa2_eth_priv {int num_channels; struct dpaa2_eth_channel** channel; TYPE_2__* net_dev; } ;
struct dpaa2_eth_channel {int /*<<< orphan*/  nctx; int /*<<< orphan*/  dpio; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpaa2_io_service_deregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  free_channel (struct dpaa2_eth_priv*,struct dpaa2_eth_channel*) ; 

__attribute__((used)) static void free_dpio(struct dpaa2_eth_priv *priv)
{
	struct device *dev = priv->net_dev->dev.parent;
	struct dpaa2_eth_channel *ch;
	int i;

	/* deregister CDAN notifications and free channels */
	for (i = 0; i < priv->num_channels; i++) {
		ch = priv->channel[i];
		dpaa2_io_service_deregister(ch->dpio, &ch->nctx, dev);
		free_channel(priv, ch);
	}
}