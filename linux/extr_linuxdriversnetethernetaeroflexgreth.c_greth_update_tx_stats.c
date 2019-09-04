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
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int GRETH_TXBD_ERR_AL ; 
 int GRETH_TXBD_ERR_LC ; 
 int GRETH_TXBD_ERR_UE ; 
 int GRETH_TXBD_STATUS ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void greth_update_tx_stats(struct net_device *dev, u32 stat)
{
	/* Check status for errors */
	if (unlikely(stat & GRETH_TXBD_STATUS)) {
		dev->stats.tx_errors++;
		if (stat & GRETH_TXBD_ERR_AL)
			dev->stats.tx_aborted_errors++;
		if (stat & GRETH_TXBD_ERR_UE)
			dev->stats.tx_fifo_errors++;
		if (stat & GRETH_TXBD_ERR_LC)
			dev->stats.tx_aborted_errors++;
	}
	dev->stats.tx_packets++;
}