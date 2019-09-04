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
struct net_device {int dummy; } ;
struct mac_device {struct fman_port** port; } ;
struct fman_port {int dummy; } ;
struct dpaa_priv {int keygen_in_use; struct mac_device* mac_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  fman_port_use_kg_hash (struct fman_port*,int) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void dpaa_set_hash(struct net_device *net_dev, bool enable)
{
	struct mac_device *mac_dev;
	struct fman_port *rxport;
	struct dpaa_priv *priv;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;
	rxport = mac_dev->port[0];

	fman_port_use_kg_hash(rxport, enable);
	priv->keygen_in_use = enable;
}