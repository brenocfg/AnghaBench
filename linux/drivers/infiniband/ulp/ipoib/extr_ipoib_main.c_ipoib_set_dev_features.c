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
struct ipoib_dev_priv {int hca_caps; TYPE_3__* dev; TYPE_2__* ca; } ;
struct TYPE_6__ {int hw_features; int features; } ;
struct TYPE_4__ {int device_cap_flags; } ;
struct TYPE_5__ {TYPE_1__ attrs; } ;

/* Variables and functions */
 int IB_DEVICE_UD_IP_CSUM ; 
 int IB_DEVICE_UD_TSO ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_TSO ; 

__attribute__((used)) static void ipoib_set_dev_features(struct ipoib_dev_priv *priv)
{
	priv->hca_caps = priv->ca->attrs.device_cap_flags;

	if (priv->hca_caps & IB_DEVICE_UD_IP_CSUM) {
		priv->dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_RXCSUM;

		if (priv->hca_caps & IB_DEVICE_UD_TSO)
			priv->dev->hw_features |= NETIF_F_TSO;

		priv->dev->features |= priv->dev->hw_features;
	}
}