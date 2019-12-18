#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gfar_private {int uses_rxfcb; scalar_t__ rx_filer_enable; scalar_t__ hwts_rx_en; TYPE_1__* ndev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 

__attribute__((used)) static void gfar_rx_offload_en(struct gfar_private *priv)
{
	/* set this when rx hw offload (TOE) functions are being used */
	priv->uses_rxfcb = 0;

	if (priv->ndev->features & (NETIF_F_RXCSUM | NETIF_F_HW_VLAN_CTAG_RX))
		priv->uses_rxfcb = 1;

	if (priv->hwts_rx_en || priv->rx_filer_enable)
		priv->uses_rxfcb = 1;
}