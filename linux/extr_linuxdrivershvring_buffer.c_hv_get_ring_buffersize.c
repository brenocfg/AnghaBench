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
typedef  int /*<<< orphan*/  u32 ;
struct hv_ring_buffer_info {int /*<<< orphan*/  ring_datasize; } ;

/* Variables and functions */

__attribute__((used)) static inline u32
hv_get_ring_buffersize(const struct hv_ring_buffer_info *ring_info)
{
	return ring_info->ring_datasize;
}