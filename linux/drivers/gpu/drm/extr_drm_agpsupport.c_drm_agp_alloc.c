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
typedef  scalar_t__ u32 ;
struct drm_device {TYPE_1__* agp; } ;
struct drm_agp_mem {unsigned long handle; unsigned long pages; int /*<<< orphan*/  head; scalar_t__ bound; struct agp_memory* memory; } ;
struct drm_agp_buffer {int size; unsigned long handle; int /*<<< orphan*/  physical; scalar_t__ type; } ;
struct agp_memory {int /*<<< orphan*/  physical; scalar_t__ key; } ;
struct TYPE_2__ {int /*<<< orphan*/  memory; int /*<<< orphan*/  bridge; int /*<<< orphan*/  acquired; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 struct agp_memory* agp_allocate_memory (int /*<<< orphan*/ ,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct drm_agp_mem*) ; 
 struct drm_agp_mem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int drm_agp_alloc(struct drm_device *dev, struct drm_agp_buffer *request)
{
	struct drm_agp_mem *entry;
	struct agp_memory *memory;
	unsigned long pages;
	u32 type;

	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;
	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	pages = (request->size + PAGE_SIZE - 1) / PAGE_SIZE;
	type = (u32) request->type;
	memory = agp_allocate_memory(dev->agp->bridge, pages, type);
	if (!memory) {
		kfree(entry);
		return -ENOMEM;
	}

	entry->handle = (unsigned long)memory->key + 1;
	entry->memory = memory;
	entry->bound = 0;
	entry->pages = pages;
	list_add(&entry->head, &dev->agp->memory);

	request->handle = entry->handle;
	request->physical = memory->physical;

	return 0;
}