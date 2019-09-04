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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  collisions; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int TX_FIFO_UNDERRUN ; 
 int TX_LATE_COLLISION ; 
 int TX_PACKET_DROPPED ; 

__attribute__((used)) static void nb8800_tx_error(struct net_device *dev, u32 report)
{
	if (report & TX_LATE_COLLISION)
		dev->stats.collisions++;

	if (report & TX_PACKET_DROPPED)
		dev->stats.tx_dropped++;

	if (report & TX_FIFO_UNDERRUN)
		dev->stats.tx_fifo_errors++;

	dev->stats.tx_errors++;
}