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
struct net_device {scalar_t__ base_addr; } ;
struct Am79C960 {int /*<<< orphan*/  RDP; } ;

/* Variables and functions */
 int /*<<< orphan*/  ariadne_reset (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void ariadne_tx_timeout(struct net_device *dev)
{
	volatile struct Am79C960 *lance = (struct Am79C960 *)dev->base_addr;

	netdev_err(dev, "transmit timed out, status %04x, resetting\n",
		   lance->RDP);
	ariadne_reset(dev);
	netif_wake_queue(dev);
}