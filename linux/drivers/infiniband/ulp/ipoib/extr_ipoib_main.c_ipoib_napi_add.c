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
 int /*<<< orphan*/  IPOIB_NUM_WC ; 
 int /*<<< orphan*/  MAX_SEND_CQE ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_rx_poll ; 
 int /*<<< orphan*/  ipoib_tx_poll ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipoib_napi_add(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	netif_napi_add(dev, &priv->recv_napi, ipoib_rx_poll, IPOIB_NUM_WC);
	netif_napi_add(dev, &priv->send_napi, ipoib_tx_poll, MAX_SEND_CQE);
}