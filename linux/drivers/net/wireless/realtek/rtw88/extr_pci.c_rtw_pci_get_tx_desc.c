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
typedef  int u8 ;
struct TYPE_2__ {int desc_size; void* head; } ;
struct rtw_pci_tx_ring {TYPE_1__ r; } ;

/* Variables and functions */

__attribute__((used)) static inline void *rtw_pci_get_tx_desc(struct rtw_pci_tx_ring *tx_ring, u8 idx)
{
	int offset = tx_ring->r.desc_size * idx;

	return tx_ring->r.head + offset;
}