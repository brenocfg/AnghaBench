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
struct net_device {int flags; } ;
struct hisi_femac_priv {int dummy; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  hisi_femac_set_mc_addr_filter (struct hisi_femac_priv*) ; 
 int /*<<< orphan*/  hisi_femac_set_promisc_mode (struct hisi_femac_priv*,int) ; 
 int /*<<< orphan*/  hisi_femac_set_uc_addr_filter (struct hisi_femac_priv*) ; 
 struct hisi_femac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void hisi_femac_net_set_rx_mode(struct net_device *dev)
{
	struct hisi_femac_priv *priv = netdev_priv(dev);

	if (dev->flags & IFF_PROMISC) {
		hisi_femac_set_promisc_mode(priv, true);
	} else {
		hisi_femac_set_promisc_mode(priv, false);
		hisi_femac_set_mc_addr_filter(priv);
		hisi_femac_set_uc_addr_filter(priv);
	}
}