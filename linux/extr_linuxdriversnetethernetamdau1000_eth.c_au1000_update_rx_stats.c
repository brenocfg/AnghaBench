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
typedef  int u32 ;
struct net_device_stats {int rx_bytes; int /*<<< orphan*/  collisions; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int RX_COLL ; 
 int RX_CRC_ERROR ; 
 int RX_ERROR ; 
 int RX_FRAME_LEN_MASK ; 
 int RX_LEN_ERROR ; 
 int RX_MCAST_FRAME ; 
 int RX_MISSED_FRAME ; 
 int RX_OVERLEN ; 
 int RX_RUNT ; 

__attribute__((used)) static inline void au1000_update_rx_stats(struct net_device *dev, u32 status)
{
	struct net_device_stats *ps = &dev->stats;

	ps->rx_packets++;
	if (status & RX_MCAST_FRAME)
		ps->multicast++;

	if (status & RX_ERROR) {
		ps->rx_errors++;
		if (status & RX_MISSED_FRAME)
			ps->rx_missed_errors++;
		if (status & (RX_OVERLEN | RX_RUNT | RX_LEN_ERROR))
			ps->rx_length_errors++;
		if (status & RX_CRC_ERROR)
			ps->rx_crc_errors++;
		if (status & RX_COLL)
			ps->collisions++;
	} else
		ps->rx_bytes += status & RX_FRAME_LEN_MASK;

}