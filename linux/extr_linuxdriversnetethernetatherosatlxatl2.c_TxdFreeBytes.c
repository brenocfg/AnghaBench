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
struct atl2_adapter {int txd_write_ptr; int txd_ring_size; int /*<<< orphan*/  txd_read_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int TxdFreeBytes(struct atl2_adapter *adapter)
{
	u32 txd_read_ptr = (u32)atomic_read(&adapter->txd_read_ptr);

	return (adapter->txd_write_ptr >= txd_read_ptr) ?
		(int) (adapter->txd_ring_size - adapter->txd_write_ptr +
		txd_read_ptr - 1) :
		(int) (txd_read_ptr - adapter->txd_write_ptr - 1);
}