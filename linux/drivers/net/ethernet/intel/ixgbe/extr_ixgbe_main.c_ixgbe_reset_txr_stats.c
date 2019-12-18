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
struct ixgbe_ring {int /*<<< orphan*/  tx_stats; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixgbe_reset_txr_stats(struct ixgbe_ring *tx_ring)
{
	memset(&tx_ring->stats, 0, sizeof(tx_ring->stats));
	memset(&tx_ring->tx_stats, 0, sizeof(tx_ring->tx_stats));
}