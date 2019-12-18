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
struct atl1c_tpd_ring {scalar_t__ desc; struct atl1c_buffer* buffer_info; } ;
struct atl1c_tpd_desc {int dummy; } ;
struct atl1c_buffer {int dummy; } ;
struct atl1c_adapter {struct atl1c_tpd_ring* tpd_ring; } ;

/* Variables and functions */

__attribute__((used)) static struct atl1c_buffer *
atl1c_get_tx_buffer(struct atl1c_adapter *adapter, struct atl1c_tpd_desc *tpd)
{
	struct atl1c_tpd_ring *tpd_ring = adapter->tpd_ring;

	return &tpd_ring->buffer_info[tpd -
			(struct atl1c_tpd_desc *)tpd_ring->desc];
}