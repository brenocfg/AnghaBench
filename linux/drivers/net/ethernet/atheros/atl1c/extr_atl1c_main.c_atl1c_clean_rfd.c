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
struct atl1c_rfd_ring {scalar_t__ count; scalar_t__ next_to_clean; struct atl1c_buffer* buffer_info; } ;
struct atl1c_recv_ret_status {scalar_t__ word0; } ;
struct atl1c_buffer {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL1C_BUFFER_FREE ; 
 int /*<<< orphan*/  ATL1C_SET_BUFFER_STATE (struct atl1c_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ RRS_RX_RFD_INDEX_MASK ; 
 scalar_t__ RRS_RX_RFD_INDEX_SHIFT ; 

__attribute__((used)) static void atl1c_clean_rfd(struct atl1c_rfd_ring *rfd_ring,
	struct atl1c_recv_ret_status *rrs, u16 num)
{
	u16 i;
	u16 rfd_index;
	struct atl1c_buffer *buffer_info = rfd_ring->buffer_info;

	rfd_index = (rrs->word0 >> RRS_RX_RFD_INDEX_SHIFT) &
			RRS_RX_RFD_INDEX_MASK;
	for (i = 0; i < num; i++) {
		buffer_info[rfd_index].skb = NULL;
		ATL1C_SET_BUFFER_STATE(&buffer_info[rfd_index],
					ATL1C_BUFFER_FREE);
		if (++rfd_index == rfd_ring->count)
			rfd_index = 0;
	}
	rfd_ring->next_to_clean = rfd_index;
}