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
struct compress {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_FAIL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  i915_memcpy_from_wc (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 void* pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compress_page(struct compress *c,
			 void *src,
			 struct drm_i915_error_object *dst)
{
	void *ptr;

	ptr = pool_alloc(&c->pool, ALLOW_FAIL);
	if (!ptr)
		return -ENOMEM;

	if (!i915_memcpy_from_wc(ptr, src, PAGE_SIZE))
		memcpy(ptr, src, PAGE_SIZE);
	dst->pages[dst->page_count++] = ptr;

	return 0;
}