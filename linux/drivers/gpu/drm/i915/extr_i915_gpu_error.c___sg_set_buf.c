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
struct scatterlist {unsigned long page_link; unsigned int length; int /*<<< orphan*/  dma_address; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  offset_in_page (void*) ; 
 scalar_t__ virt_to_page (void*) ; 

__attribute__((used)) static void __sg_set_buf(struct scatterlist *sg,
			 void *addr, unsigned int len, loff_t it)
{
	sg->page_link = (unsigned long)virt_to_page(addr);
	sg->offset = offset_in_page(addr);
	sg->length = len;
	sg->dma_address = it;
}