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
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int IntrRxPCIErr ; 
 int IntrRxPCIFault ; 
 int IntrTxPCIErr ; 
 int IntrTxPCIFault ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 

__attribute__((used)) static void yellowfin_error(struct net_device *dev, int intr_status)
{
	netdev_err(dev, "Something Wicked happened! %04x\n", intr_status);
	/* Hmmmmm, it's not clear what to do here. */
	if (intr_status & (IntrTxPCIErr | IntrTxPCIFault))
		dev->stats.tx_errors++;
	if (intr_status & (IntrRxPCIErr | IntrRxPCIFault))
		dev->stats.rx_errors++;
}