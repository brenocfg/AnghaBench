#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int enable; } ;
struct TYPE_5__ {int /*<<< orphan*/  rssen; } ;
struct stmmac_priv {TYPE_2__* plat; TYPE_4__ rss; int /*<<< orphan*/  hw; TYPE_3__* dev; TYPE_1__ dma_cap; } ;
struct TYPE_7__ {int features; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_queues_to_use; int /*<<< orphan*/  rss_en; } ;

/* Variables and functions */
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  stmmac_rss_configure (struct stmmac_priv*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_mac_config_rss(struct stmmac_priv *priv)
{
	if (!priv->dma_cap.rssen || !priv->plat->rss_en) {
		priv->rss.enable = false;
		return;
	}

	if (priv->dev->features & NETIF_F_RXHASH)
		priv->rss.enable = true;
	else
		priv->rss.enable = false;

	stmmac_rss_configure(priv, priv->hw, &priv->rss,
			     priv->plat->rx_queues_to_use);
}