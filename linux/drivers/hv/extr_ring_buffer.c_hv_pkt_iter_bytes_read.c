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
typedef  scalar_t__ u32 ;
struct hv_ring_buffer_info {scalar_t__ priv_read_index; scalar_t__ ring_datasize; } ;

/* Variables and functions */

__attribute__((used)) static u32 hv_pkt_iter_bytes_read(const struct hv_ring_buffer_info *rbi,
					u32 start_read_index)
{
	if (rbi->priv_read_index >= start_read_index)
		return rbi->priv_read_index - start_read_index;
	else
		return rbi->ring_datasize - start_read_index +
			rbi->priv_read_index;
}