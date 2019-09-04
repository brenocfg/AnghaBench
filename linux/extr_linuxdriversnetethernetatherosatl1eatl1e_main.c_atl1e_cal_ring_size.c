#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct atl1e_tpd_desc {int dummy; } ;
struct TYPE_4__ {int real_page_size; } ;
struct TYPE_3__ {int count; } ;
struct atl1e_adapter {int num_rx_queues; TYPE_2__ rx_ring; TYPE_1__ tx_ring; } ;

/* Variables and functions */
 int AT_PAGE_NUM_PER_QUEUE ; 

__attribute__((used)) static void atl1e_cal_ring_size(struct atl1e_adapter *adapter, u32 *ring_size)
{
	*ring_size = ((u32)(adapter->tx_ring.count *
		     sizeof(struct atl1e_tpd_desc) + 7
			/* tx ring, qword align */
		     + adapter->rx_ring.real_page_size * AT_PAGE_NUM_PER_QUEUE *
			adapter->num_rx_queues + 31
			/* rx ring,  32 bytes align */
		     + (1 + AT_PAGE_NUM_PER_QUEUE * adapter->num_rx_queues) *
			sizeof(u32) + 3));
			/* tx, rx cmd, dword align   */
}