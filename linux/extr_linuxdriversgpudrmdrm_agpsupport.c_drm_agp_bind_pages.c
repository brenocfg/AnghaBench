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
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct drm_device {TYPE_1__* agp; } ;
struct agp_memory {unsigned long page_count; int is_flushed; struct page** pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int PAGE_SIZE ; 
 struct agp_memory* agp_allocate_memory (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int agp_bind_memory (struct agp_memory*,int) ; 
 int /*<<< orphan*/  agp_free_memory (struct agp_memory*) ; 

struct agp_memory *
drm_agp_bind_pages(struct drm_device *dev,
		   struct page **pages,
		   unsigned long num_pages,
		   uint32_t gtt_offset,
		   u32 type)
{
	struct agp_memory *mem;
	int ret, i;

	DRM_DEBUG("\n");

	mem = agp_allocate_memory(dev->agp->bridge, num_pages,
				      type);
	if (mem == NULL) {
		DRM_ERROR("Failed to allocate memory for %ld pages\n",
			  num_pages);
		return NULL;
	}

	for (i = 0; i < num_pages; i++)
		mem->pages[i] = pages[i];
	mem->page_count = num_pages;

	mem->is_flushed = true;
	ret = agp_bind_memory(mem, gtt_offset / PAGE_SIZE);
	if (ret != 0) {
		DRM_ERROR("Failed to bind AGP memory: %d\n", ret);
		agp_free_memory(mem);
		return NULL;
	}

	return mem;
}