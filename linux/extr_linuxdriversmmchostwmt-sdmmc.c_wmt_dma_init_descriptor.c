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
typedef  void* u32 ;
typedef  int u16 ;
struct wmt_dma_descriptor {int flags; void* branch_addr; void* data_buffer_addr; } ;

/* Variables and functions */

__attribute__((used)) static void wmt_dma_init_descriptor(struct wmt_dma_descriptor *desc,
		u16 req_count, u32 buffer_addr, u32 branch_addr, int end)
{
	desc->flags = 0x40000000 | req_count;
	if (end)
		desc->flags |= 0x80000000;
	desc->data_buffer_addr = buffer_addr;
	desc->branch_addr = branch_addr;
}