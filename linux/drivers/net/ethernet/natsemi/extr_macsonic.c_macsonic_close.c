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
struct net_device {scalar_t__ irq; } ;

/* Variables and functions */
 scalar_t__ IRQ_AUTO_3 ; 
 scalar_t__ IRQ_NUBUS_9 ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int sonic_close (struct net_device*) ; 

__attribute__((used)) static int macsonic_close(struct net_device* dev)
{
	int err;
	err = sonic_close(dev);
	free_irq(dev->irq, dev);
	if (dev->irq == IRQ_AUTO_3)
		free_irq(IRQ_NUBUS_9, dev);
	return err;
}