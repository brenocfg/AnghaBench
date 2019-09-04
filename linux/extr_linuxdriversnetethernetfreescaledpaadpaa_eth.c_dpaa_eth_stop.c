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
struct dpaa_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpaa_eth_napi_disable (struct dpaa_priv*) ; 
 int dpaa_stop (struct net_device*) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dpaa_eth_stop(struct net_device *net_dev)
{
	struct dpaa_priv *priv;
	int err;

	err = dpaa_stop(net_dev);

	priv = netdev_priv(net_dev);
	dpaa_eth_napi_disable(priv);

	return err;
}