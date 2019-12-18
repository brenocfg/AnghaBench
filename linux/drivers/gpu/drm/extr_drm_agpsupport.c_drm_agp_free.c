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
struct drm_device {TYPE_1__* agp; } ;
struct drm_agp_mem {int /*<<< orphan*/  pages; int /*<<< orphan*/  memory; int /*<<< orphan*/  head; scalar_t__ bound; } ;
struct drm_agp_buffer {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  acquired; } ;

/* Variables and functions */
 int EINVAL ; 
 struct drm_agp_mem* drm_agp_lookup_entry (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_free_agp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_unbind_agp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_agp_mem*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

int drm_agp_free(struct drm_device *dev, struct drm_agp_buffer *request)
{
	struct drm_agp_mem *entry;

	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;
	entry = drm_agp_lookup_entry(dev, request->handle);
	if (!entry)
		return -EINVAL;
	if (entry->bound)
		drm_unbind_agp(entry->memory);

	list_del(&entry->head);

	drm_free_agp(entry->memory, entry->pages);
	kfree(entry);
	return 0;
}