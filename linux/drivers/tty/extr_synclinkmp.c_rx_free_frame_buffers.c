#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int rx_buf_count; unsigned int current_rx_buf; TYPE_2__* rx_buf_list_ex; TYPE_1__* rx_buf_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  phys_entry; } ;
struct TYPE_6__ {int status; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ EDA ; 
 scalar_t__ RXDMA ; 
 int /*<<< orphan*/  write_reg16 (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_free_frame_buffers(SLMP_INFO *info, unsigned int first, unsigned int last)
{
	bool done = false;

	while(!done) {
	        /* reset current buffer for reuse */
		info->rx_buf_list[first].status = 0xff;

	        if (first == last) {
	                done = true;
	                /* set new last rx descriptor address */
			write_reg16(info, RXDMA + EDA, info->rx_buf_list_ex[first].phys_entry);
	        }

	        first++;
		if (first == info->rx_buf_count)
			first = 0;
	}

	/* set current buffer to next buffer after last buffer of frame */
	info->current_rx_buf = first;
}