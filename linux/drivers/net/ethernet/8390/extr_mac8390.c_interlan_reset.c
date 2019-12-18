#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  irq; } ;
struct ei_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ txing; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ2SLOT (int /*<<< orphan*/ ) ; 
 TYPE_1__ ei_status ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  jiffies ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct ei_device*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_hw (struct ei_device*) ; 
 unsigned char* nubus_slot_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 

__attribute__((used)) static void interlan_reset(struct net_device *dev)
{
	unsigned char *target = nubus_slot_addr(IRQ2SLOT(dev->irq));
	struct ei_device *ei_local = netdev_priv(dev);

	netif_info(ei_local, hw, dev, "Need to reset the NS8390 t=%lu...",
		   jiffies);
	ei_status.txing = 0;
	target[0xC0000] = 0;
	if (netif_msg_hw(ei_local))
		pr_cont("reset complete\n");
}