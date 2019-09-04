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
struct pxa168_eth_private {int /*<<< orphan*/  napi; scalar_t__ rx_curr_desc_q; scalar_t__ rx_used_desc_q; scalar_t__ rx_resource_err; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  eth_port_start (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  pxa168_eth_int_handler ; 
 int pxa168_init_phy (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  rxq_deinit (struct net_device*) ; 
 int rxq_init (struct net_device*) ; 
 int /*<<< orphan*/  rxq_refill (struct net_device*) ; 
 int txq_init (struct net_device*) ; 

__attribute__((used)) static int pxa168_eth_open(struct net_device *dev)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);
	int err;

	err = pxa168_init_phy(dev);
	if (err)
		return err;

	err = request_irq(dev->irq, pxa168_eth_int_handler, 0, dev->name, dev);
	if (err) {
		dev_err(&dev->dev, "can't assign irq\n");
		return -EAGAIN;
	}
	pep->rx_resource_err = 0;
	err = rxq_init(dev);
	if (err != 0)
		goto out_free_irq;
	err = txq_init(dev);
	if (err != 0)
		goto out_free_rx_skb;
	pep->rx_used_desc_q = 0;
	pep->rx_curr_desc_q = 0;

	/* Fill RX ring with skb's */
	rxq_refill(dev);
	pep->rx_used_desc_q = 0;
	pep->rx_curr_desc_q = 0;
	netif_carrier_off(dev);
	napi_enable(&pep->napi);
	eth_port_start(dev);
	return 0;
out_free_rx_skb:
	rxq_deinit(dev);
out_free_irq:
	free_irq(dev->irq, dev);
	return err;
}