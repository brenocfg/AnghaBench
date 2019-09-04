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
struct net_device {int /*<<< orphan*/  name; } ;
struct ep93xx_priv {int /*<<< orphan*/  napi; int /*<<< orphan*/  irq; scalar_t__ tx_pending; int /*<<< orphan*/  tx_pending_lock; scalar_t__ tx_pointer; scalar_t__ tx_clean_pointer; scalar_t__ rx_pointer; int /*<<< orphan*/  rx_lock; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  REG_GIINTMSK ; 
 int /*<<< orphan*/  REG_GIINTMSK_ENABLE ; 
 scalar_t__ ep93xx_alloc_buffers (struct ep93xx_priv*) ; 
 int /*<<< orphan*/  ep93xx_free_buffers (struct ep93xx_priv*) ; 
 int /*<<< orphan*/  ep93xx_irq ; 
 scalar_t__ ep93xx_start_hw (struct net_device*) ; 
 int /*<<< orphan*/  ep93xx_stop_hw (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct ep93xx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrl (struct ep93xx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xx_open(struct net_device *dev)
{
	struct ep93xx_priv *ep = netdev_priv(dev);
	int err;

	if (ep93xx_alloc_buffers(ep))
		return -ENOMEM;

	napi_enable(&ep->napi);

	if (ep93xx_start_hw(dev)) {
		napi_disable(&ep->napi);
		ep93xx_free_buffers(ep);
		return -EIO;
	}

	spin_lock_init(&ep->rx_lock);
	ep->rx_pointer = 0;
	ep->tx_clean_pointer = 0;
	ep->tx_pointer = 0;
	spin_lock_init(&ep->tx_pending_lock);
	ep->tx_pending = 0;

	err = request_irq(ep->irq, ep93xx_irq, IRQF_SHARED, dev->name, dev);
	if (err) {
		napi_disable(&ep->napi);
		ep93xx_stop_hw(dev);
		ep93xx_free_buffers(ep);
		return err;
	}

	wrl(ep, REG_GIINTMSK, REG_GIINTMSK_ENABLE);

	netif_start_queue(dev);

	return 0;
}