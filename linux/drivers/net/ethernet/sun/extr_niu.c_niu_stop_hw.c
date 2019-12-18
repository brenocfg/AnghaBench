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
struct niu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  netif_printk (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  niu_disable_ipp (struct niu*) ; 
 int /*<<< orphan*/  niu_enable_interrupts (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_enable_rx_mac (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_reset_rx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_reset_tx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_stop_rx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_stop_tx_channels (struct niu*) ; 

__attribute__((used)) static void niu_stop_hw(struct niu *np)
{
	netif_printk(np, ifdown, KERN_DEBUG, np->dev, "Disable interrupts\n");
	niu_enable_interrupts(np, 0);

	netif_printk(np, ifdown, KERN_DEBUG, np->dev, "Disable RX MAC\n");
	niu_enable_rx_mac(np, 0);

	netif_printk(np, ifdown, KERN_DEBUG, np->dev, "Disable IPP\n");
	niu_disable_ipp(np);

	netif_printk(np, ifdown, KERN_DEBUG, np->dev, "Stop TX channels\n");
	niu_stop_tx_channels(np);

	netif_printk(np, ifdown, KERN_DEBUG, np->dev, "Stop RX channels\n");
	niu_stop_rx_channels(np);

	netif_printk(np, ifdown, KERN_DEBUG, np->dev, "Reset TX channels\n");
	niu_reset_tx_channels(np);

	netif_printk(np, ifdown, KERN_DEBUG, np->dev, "Reset RX channels\n");
	niu_reset_rx_channels(np);
}