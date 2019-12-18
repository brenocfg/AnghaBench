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
struct TYPE_2__ {scalar_t__ offset; } ;
struct st_buffer {int reserved_page_order; int frp_segs; int buffer_size; TYPE_1__ map_data; scalar_t__ sg_segs; int /*<<< orphan*/ * reserved_pages; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void normalize_buffer(struct st_buffer * STbuffer)
{
	int i, order = STbuffer->reserved_page_order;

	for (i = 0; i < STbuffer->frp_segs; i++) {
		__free_pages(STbuffer->reserved_pages[i], order);
		STbuffer->buffer_size -= (PAGE_SIZE << order);
	}
	STbuffer->frp_segs = 0;
	STbuffer->sg_segs = 0;
	STbuffer->reserved_page_order = 0;
	STbuffer->map_data.offset = 0;
}