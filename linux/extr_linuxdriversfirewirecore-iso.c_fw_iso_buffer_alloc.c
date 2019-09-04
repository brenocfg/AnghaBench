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
struct fw_iso_buffer {int page_count; int /*<<< orphan*/ ** pages; scalar_t__ page_count_mapped; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/ * alloc_page (int) ; 
 int /*<<< orphan*/  fw_iso_buffer_destroy (struct fw_iso_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** kmalloc_array (int,int,int) ; 

int fw_iso_buffer_alloc(struct fw_iso_buffer *buffer, int page_count)
{
	int i;

	buffer->page_count = 0;
	buffer->page_count_mapped = 0;
	buffer->pages = kmalloc_array(page_count, sizeof(buffer->pages[0]),
				      GFP_KERNEL);
	if (buffer->pages == NULL)
		return -ENOMEM;

	for (i = 0; i < page_count; i++) {
		buffer->pages[i] = alloc_page(GFP_KERNEL | GFP_DMA32 | __GFP_ZERO);
		if (buffer->pages[i] == NULL)
			break;
	}
	buffer->page_count = i;
	if (i < page_count) {
		fw_iso_buffer_destroy(buffer, NULL);
		return -ENOMEM;
	}

	return 0;
}