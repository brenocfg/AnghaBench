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
struct net_device {int dummy; } ;
struct ei_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ dmaing; scalar_t__ txing; } ;

/* Variables and functions */
 scalar_t__ EN0_ISR ; 
 int ENISR_RESET ; 
 scalar_t__ NE_BASE ; 
 scalar_t__ NE_RESET ; 
 TYPE_1__ ei_status ; 
 int /*<<< orphan*/  hw ; 
 int inb (scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct ei_device*,int /*<<< orphan*/ ,struct net_device*,char*,unsigned long) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void ne2k_pci_reset_8390(struct net_device *dev)
{
	unsigned long reset_start_time = jiffies;
	struct ei_device *ei_local = netdev_priv(dev);

	netif_dbg(ei_local, hw, dev, "resetting the 8390 t=%ld...\n",
		  jiffies);

	outb(inb(NE_BASE + NE_RESET), NE_BASE + NE_RESET);

	ei_status.txing = 0;
	ei_status.dmaing = 0;

	/* This check _should_not_ be necessary, omit eventually. */
	while ((inb(NE_BASE+EN0_ISR) & ENISR_RESET) == 0)
		if (jiffies - reset_start_time > 2) {
			netdev_err(dev, "ne2k_pci_reset_8390() did not complete.\n");
			break;
		}
	outb(ENISR_RESET, NE_BASE + EN0_ISR);	/* Ack intr. */
}