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
typedef  scalar_t__ u16 ;
struct atl1e_tx_ring {scalar_t__ next_to_use; scalar_t__ count; int /*<<< orphan*/  next_to_clean; } ;
struct atl1e_adapter {struct atl1e_tx_ring tx_ring; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u16 atl1e_tpd_avail(struct atl1e_adapter *adapter)
{
	struct atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	u16 next_to_use = 0;
	u16 next_to_clean = 0;

	next_to_clean = atomic_read(&tx_ring->next_to_clean);
	next_to_use   = tx_ring->next_to_use;

	return (u16)(next_to_clean > next_to_use) ?
		(next_to_clean - next_to_use - 1) :
		(tx_ring->count + next_to_clean - next_to_use - 1);
}