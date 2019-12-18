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
struct drm_device {int /*<<< orphan*/ * vma_offset_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_vma_offset_manager_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void
drm_gem_destroy(struct drm_device *dev)
{

	drm_vma_offset_manager_destroy(dev->vma_offset_manager);
	kfree(dev->vma_offset_manager);
	dev->vma_offset_manager = NULL;
}