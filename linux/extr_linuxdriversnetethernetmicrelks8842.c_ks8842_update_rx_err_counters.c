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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int RXSR_CRC_ERROR ; 
 int RXSR_RUNT ; 
 int RXSR_TOO_LONG ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 

__attribute__((used)) static void ks8842_update_rx_err_counters(struct net_device *netdev, u32 status)
{
	netdev_dbg(netdev, "RX error, status: %x\n", status);

	netdev->stats.rx_errors++;
	if (status & RXSR_TOO_LONG)
		netdev->stats.rx_length_errors++;
	if (status & RXSR_CRC_ERROR)
		netdev->stats.rx_crc_errors++;
	if (status & RXSR_RUNT)
		netdev->stats.rx_frame_errors++;
}