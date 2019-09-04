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
struct drm_i915_error_object {int /*<<< orphan*/  page_count; void** pages; } ;
struct compress {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_NOWARN ; 
 unsigned long __get_free_page (int) ; 
 int /*<<< orphan*/  i915_memcpy_from_wc (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compress_page(struct compress *c,
			 void *src,
			 struct drm_i915_error_object *dst)
{
	unsigned long page;
	void *ptr;

	page = __get_free_page(GFP_ATOMIC | __GFP_NOWARN);
	if (!page)
		return -ENOMEM;

	ptr = (void *)page;
	if (!i915_memcpy_from_wc(ptr, src, PAGE_SIZE))
		memcpy(ptr, src, PAGE_SIZE);
	dst->pages[dst->page_count++] = ptr;

	return 0;
}