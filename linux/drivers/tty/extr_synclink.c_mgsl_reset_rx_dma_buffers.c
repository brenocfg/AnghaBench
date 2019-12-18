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
struct mgsl_struct {unsigned int rx_buffer_count; scalar_t__ current_rx_buffer; TYPE_1__* rx_buffer_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 unsigned long DMABUFFERSIZE ; 

__attribute__((used)) static void mgsl_reset_rx_dma_buffers( struct mgsl_struct *info )
{
	unsigned int i;

	for ( i = 0; i < info->rx_buffer_count; i++ ) {
		*((unsigned long *)&(info->rx_buffer_list[i].count)) = DMABUFFERSIZE;
//		info->rx_buffer_list[i].count = DMABUFFERSIZE;
//		info->rx_buffer_list[i].status = 0;
	}

	info->current_rx_buffer = 0;

}