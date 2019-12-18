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
struct velocity_info {int /*<<< orphan*/ * mib_counter; int /*<<< orphan*/  lock; } ;
struct net_device_stats {int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 size_t HW_MIB_ifInRangeLengthErrors ; 
 size_t HW_MIB_ifRxAllPkts ; 
 size_t HW_MIB_ifRxErrorPkts ; 
 size_t HW_MIB_ifRxPktCRCE ; 
 size_t HW_MIB_ifTxEtherCollisions ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  velocity_update_hw_mibs (struct velocity_info*) ; 

__attribute__((used)) static struct net_device_stats *velocity_get_stats(struct net_device *dev)
{
	struct velocity_info *vptr = netdev_priv(dev);

	/* If the hardware is down, don't touch MII */
	if (!netif_running(dev))
		return &dev->stats;

	spin_lock_irq(&vptr->lock);
	velocity_update_hw_mibs(vptr);
	spin_unlock_irq(&vptr->lock);

	dev->stats.rx_packets = vptr->mib_counter[HW_MIB_ifRxAllPkts];
	dev->stats.rx_errors = vptr->mib_counter[HW_MIB_ifRxErrorPkts];
	dev->stats.rx_length_errors = vptr->mib_counter[HW_MIB_ifInRangeLengthErrors];

//  unsigned long   rx_dropped;     /* no space in linux buffers    */
	dev->stats.collisions = vptr->mib_counter[HW_MIB_ifTxEtherCollisions];
	/* detailed rx_errors: */
//  unsigned long   rx_length_errors;
//  unsigned long   rx_over_errors;     /* receiver ring buff overflow  */
	dev->stats.rx_crc_errors = vptr->mib_counter[HW_MIB_ifRxPktCRCE];
//  unsigned long   rx_frame_errors;    /* recv'd frame alignment error */
//  unsigned long   rx_fifo_errors;     /* recv'r fifo overrun      */
//  unsigned long   rx_missed_errors;   /* receiver missed packet   */

	/* detailed tx_errors */
//  unsigned long   tx_fifo_errors;

	return &dev->stats;
}