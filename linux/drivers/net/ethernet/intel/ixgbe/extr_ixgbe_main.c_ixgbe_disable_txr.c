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
struct ixgbe_ring {int /*<<< orphan*/  state; } ;
struct ixgbe_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_TX_DISABLED ; 
 int /*<<< orphan*/  ixgbe_disable_txr_hw (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_disable_txr(struct ixgbe_adapter *adapter,
			      struct ixgbe_ring *tx_ring)
{
	set_bit(__IXGBE_TX_DISABLED, &tx_ring->state);
	ixgbe_disable_txr_hw(adapter, tx_ring);
}