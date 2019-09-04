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
struct de_private {scalar_t__ tx_tail; scalar_t__ tx_head; scalar_t__ rx_tail; TYPE_1__* tx_ring; } ;
struct de_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  opts2; } ;

/* Variables and functions */
 int DE_TX_RING_SIZE ; 
 int /*<<< orphan*/  RingEnd ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int de_refill_rx (struct de_private*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int de_init_rings (struct de_private *de)
{
	memset(de->tx_ring, 0, sizeof(struct de_desc) * DE_TX_RING_SIZE);
	de->tx_ring[DE_TX_RING_SIZE - 1].opts2 = cpu_to_le32(RingEnd);

	de->rx_tail = 0;
	de->tx_head = de->tx_tail = 0;

	return de_refill_rx (de);
}