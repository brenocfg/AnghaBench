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
struct macb {int tx_ring_size; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int macb_tx_ring_wrap(struct macb *bp, unsigned int index)
{
	return index & (bp->tx_ring_size - 1);
}