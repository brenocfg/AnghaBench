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
typedef  void uint8_t ;
struct ttm_buffer_object {int dummy; } ;
struct ttm_bo_kmap_obj {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 
 unsigned long min (unsigned long,scalar_t__) ; 
 int ttm_bo_kmap (struct ttm_buffer_object*,unsigned long,int,struct ttm_bo_kmap_obj*) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (struct ttm_bo_kmap_obj*) ; 
 scalar_t__ ttm_kmap_obj_virtual (struct ttm_bo_kmap_obj*,int*) ; 

__attribute__((used)) static int ttm_bo_vm_access_kmap(struct ttm_buffer_object *bo,
				 unsigned long offset,
				 uint8_t *buf, int len, int write)
{
	unsigned long page = offset >> PAGE_SHIFT;
	unsigned long bytes_left = len;
	int ret;

	/* Copy a page at a time, that way no extra virtual address
	 * mapping is needed
	 */
	offset -= page << PAGE_SHIFT;
	do {
		unsigned long bytes = min(bytes_left, PAGE_SIZE - offset);
		struct ttm_bo_kmap_obj map;
		void *ptr;
		bool is_iomem;

		ret = ttm_bo_kmap(bo, page, 1, &map);
		if (ret)
			return ret;

		ptr = (uint8_t *)ttm_kmap_obj_virtual(&map, &is_iomem) + offset;
		WARN_ON_ONCE(is_iomem);
		if (write)
			memcpy(ptr, buf, bytes);
		else
			memcpy(buf, ptr, bytes);
		ttm_bo_kunmap(&map);

		page++;
		buf += bytes;
		bytes_left -= bytes;
		offset = 0;
	} while (bytes_left);

	return len;
}