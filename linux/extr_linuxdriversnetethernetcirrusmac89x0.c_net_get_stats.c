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
struct net_device_stats {int rx_missed_errors; int collisions; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_RxMiss ; 
 int /*<<< orphan*/  PP_TxCol ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int readreg (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device_stats *
net_get_stats(struct net_device *dev)
{
	unsigned long flags;

	local_irq_save(flags);
	/* Update the statistics from the device registers. */
	dev->stats.rx_missed_errors += (readreg(dev, PP_RxMiss) >> 6);
	dev->stats.collisions += (readreg(dev, PP_TxCol) >> 6);
	local_irq_restore(flags);

	return &dev->stats;
}