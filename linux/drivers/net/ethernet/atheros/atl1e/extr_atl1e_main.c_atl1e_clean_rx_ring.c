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
typedef  size_t u16 ;
struct atl1e_rx_ring {int /*<<< orphan*/  real_page_size; struct atl1e_rx_page_desc* rx_page_desc; } ;
struct atl1e_rx_page_desc {TYPE_1__* rx_page; } ;
struct atl1e_adapter {size_t num_rx_queues; int /*<<< orphan*/ * ring_vir_addr; struct atl1e_rx_ring rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 size_t AT_PAGE_NUM_PER_QUEUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1e_clean_rx_ring(struct atl1e_adapter *adapter)
{
	struct atl1e_rx_ring *rx_ring =
		&adapter->rx_ring;
	struct atl1e_rx_page_desc *rx_page_desc = rx_ring->rx_page_desc;
	u16 i, j;


	if (adapter->ring_vir_addr == NULL)
		return;
	/* Zero out the descriptor ring */
	for (i = 0; i < adapter->num_rx_queues; i++) {
		for (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) {
			if (rx_page_desc[i].rx_page[j].addr != NULL) {
				memset(rx_page_desc[i].rx_page[j].addr, 0,
						rx_ring->real_page_size);
			}
		}
	}
}