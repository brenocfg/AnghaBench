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
struct atl2_adapter {int txs_next_clear; int txs_ring_size; int /*<<< orphan*/  txs_write_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int TxsFreeUnit(struct atl2_adapter *adapter)
{
	u32 txs_write_ptr = (u32) atomic_read(&adapter->txs_write_ptr);

	return (adapter->txs_next_clear >= txs_write_ptr) ?
		(int) (adapter->txs_ring_size - adapter->txs_next_clear +
		txs_write_ptr - 1) :
		(int) (txs_write_ptr - adapter->txs_next_clear - 1);
}