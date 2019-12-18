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
struct atl1e_tx_ring {struct atl1e_tpd_desc* desc; struct atl1e_tx_buffer* tx_buffer; } ;
struct atl1e_tx_buffer {int dummy; } ;
struct atl1e_tpd_desc {int dummy; } ;
struct atl1e_adapter {struct atl1e_tx_ring tx_ring; } ;

/* Variables and functions */

__attribute__((used)) static struct atl1e_tx_buffer *
atl1e_get_tx_buffer(struct atl1e_adapter *adapter, struct atl1e_tpd_desc *tpd)
{
	struct atl1e_tx_ring *tx_ring = &adapter->tx_ring;

	return &tx_ring->tx_buffer[tpd - tx_ring->desc];
}