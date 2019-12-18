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
typedef  size_t u16 ;
struct ixgbe_rx_buffer {int /*<<< orphan*/  handle; } ;
struct ixgbe_ring {size_t next_to_clean; size_t next_to_alloc; size_t count; struct ixgbe_rx_buffer* rx_buffer_info; int /*<<< orphan*/  xsk_umem; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsk_umem_fq_reuse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ixgbe_xsk_clean_rx_ring(struct ixgbe_ring *rx_ring)
{
	u16 i = rx_ring->next_to_clean;
	struct ixgbe_rx_buffer *bi = &rx_ring->rx_buffer_info[i];

	while (i != rx_ring->next_to_alloc) {
		xsk_umem_fq_reuse(rx_ring->xsk_umem, bi->handle);
		i++;
		bi++;
		if (i == rx_ring->count) {
			i = 0;
			bi = rx_ring->rx_buffer_info;
		}
	}
}