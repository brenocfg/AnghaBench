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
typedef  int uint32_t ;
struct TYPE_2__ {int size_list_size; struct list_head* size_list; } ;
struct vc4_dev {TYPE_1__ bo_cache; } ;
struct list_head {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int bo_page_index (size_t) ; 
 int /*<<< orphan*/  kfree (struct list_head*) ; 
 struct list_head* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_replace (struct list_head*,struct list_head*) ; 
 int max (int,int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static struct list_head *vc4_get_cache_list_for_size(struct drm_device *dev,
						     size_t size)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	uint32_t page_index = bo_page_index(size);

	if (vc4->bo_cache.size_list_size <= page_index) {
		uint32_t new_size = max(vc4->bo_cache.size_list_size * 2,
					page_index + 1);
		struct list_head *new_list;
		uint32_t i;

		new_list = kmalloc_array(new_size, sizeof(struct list_head),
					 GFP_KERNEL);
		if (!new_list)
			return NULL;

		/* Rebase the old cached BO lists to their new list
		 * head locations.
		 */
		for (i = 0; i < vc4->bo_cache.size_list_size; i++) {
			struct list_head *old_list =
				&vc4->bo_cache.size_list[i];

			if (list_empty(old_list))
				INIT_LIST_HEAD(&new_list[i]);
			else
				list_replace(old_list, &new_list[i]);
		}
		/* And initialize the brand new BO list heads. */
		for (i = vc4->bo_cache.size_list_size; i < new_size; i++)
			INIT_LIST_HEAD(&new_list[i]);

		kfree(vc4->bo_cache.size_list);
		vc4->bo_cache.size_list = new_list;
		vc4->bo_cache.size_list_size = new_size;
	}

	return &vc4->bo_cache.size_list[page_index];
}