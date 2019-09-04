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
typedef  union i40e_rx_desc {int dummy; } i40e_rx_desc ;
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40e_rx_buffer {int /*<<< orphan*/ * page; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_reuse_count; } ;
struct i40e_ring {TYPE_1__ rx_stats; int /*<<< orphan*/  next_to_clean; int /*<<< orphan*/  count; struct i40e_rx_buffer* rx_bi; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_RX_DESC (struct i40e_ring*,int /*<<< orphan*/ ) ; 
 int I40E_RX_PROG_STATUS_DESC_FD_FILTER_STATUS ; 
 int I40E_RX_PROG_STATUS_DESC_QW1_PROGID_MASK ; 
 int I40E_RX_PROG_STATUS_DESC_QW1_PROGID_SHIFT ; 
 int /*<<< orphan*/  i40e_fd_handle_status (struct i40e_ring*,union i40e_rx_desc*,int) ; 
 int /*<<< orphan*/  i40e_reuse_rx_page (struct i40e_ring*,struct i40e_rx_buffer*) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_clean_programming_status(struct i40e_ring *rx_ring,
					  union i40e_rx_desc *rx_desc,
					  u64 qw)
{
	struct i40e_rx_buffer *rx_buffer;
	u32 ntc = rx_ring->next_to_clean;
	u8 id;

	/* fetch, update, and store next to clean */
	rx_buffer = &rx_ring->rx_bi[ntc++];
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(I40E_RX_DESC(rx_ring, ntc));

	/* place unused page back on the ring */
	i40e_reuse_rx_page(rx_ring, rx_buffer);
	rx_ring->rx_stats.page_reuse_count++;

	/* clear contents of buffer_info */
	rx_buffer->page = NULL;

	id = (qw & I40E_RX_PROG_STATUS_DESC_QW1_PROGID_MASK) >>
		  I40E_RX_PROG_STATUS_DESC_QW1_PROGID_SHIFT;

	if (id == I40E_RX_PROG_STATUS_DESC_FD_FILTER_STATUS)
		i40e_fd_handle_status(rx_ring, rx_desc, id);
}