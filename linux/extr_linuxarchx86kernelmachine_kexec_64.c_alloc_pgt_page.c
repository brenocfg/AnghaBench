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
struct page {int dummy; } ;
struct kimage {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_page (void*) ; 
 struct page* kimage_alloc_control_pages (struct kimage*,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static void *alloc_pgt_page(void *data)
{
	struct kimage *image = (struct kimage *)data;
	struct page *page;
	void *p = NULL;

	page = kimage_alloc_control_pages(image, 0);
	if (page) {
		p = page_address(page);
		clear_page(p);
	}

	return p;
}