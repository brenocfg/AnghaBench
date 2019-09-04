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
struct skge_port {size_t port; int /*<<< orphan*/  hw; int /*<<< orphan*/  netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_STOP ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_printk (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  skge_tx_clean (struct net_device*) ; 
 int /*<<< orphan*/  skge_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/ * txqaddr ; 

__attribute__((used)) static void skge_tx_timeout(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);

	netif_printk(skge, timer, KERN_DEBUG, skge->netdev, "tx timeout\n");

	skge_write8(skge->hw, Q_ADDR(txqaddr[skge->port], Q_CSR), CSR_STOP);
	skge_tx_clean(dev);
	netif_wake_queue(dev);
}