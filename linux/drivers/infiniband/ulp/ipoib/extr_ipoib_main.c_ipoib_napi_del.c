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
struct ipoib_dev_priv {int /*<<< orphan*/  send_napi; int /*<<< orphan*/  recv_napi; } ;

/* Variables and functions */
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_napi_del(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	netif_napi_del(&priv->recv_napi);
	netif_napi_del(&priv->send_napi);
}