#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netdev_private {TYPE_2__* rx_ring; TYPE_1__* tx_ring; scalar_t__ old_tx; scalar_t__ old_rx; scalar_t__ cur_tx; scalar_t__ cur_rx; } ;
struct TYPE_4__ {scalar_t__ status; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  TFDDone ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rio_reset_ring(struct netdev_private *np)
{
	int i;

	np->cur_rx = 0;
	np->cur_tx = 0;
	np->old_rx = 0;
	np->old_tx = 0;

	for (i = 0; i < TX_RING_SIZE; i++)
		np->tx_ring[i].status = cpu_to_le64(TFDDone);

	for (i = 0; i < RX_RING_SIZE; i++)
		np->rx_ring[i].status = 0;
}