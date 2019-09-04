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
struct moxart_mac_priv_t {scalar_t__ base; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 scalar_t__ REG_INTERRUPT_MASK ; 
 scalar_t__ REG_MAC_CTRL ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct moxart_mac_priv_t* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int moxart_mac_stop(struct net_device *ndev)
{
	struct moxart_mac_priv_t *priv = netdev_priv(ndev);

	napi_disable(&priv->napi);

	netif_stop_queue(ndev);

	/* disable all interrupts */
	writel(0, priv->base + REG_INTERRUPT_MASK);

	/* disable all functions */
	writel(0, priv->base + REG_MAC_CTRL);

	return 0;
}