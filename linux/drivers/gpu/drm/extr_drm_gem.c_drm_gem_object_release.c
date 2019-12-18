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
struct drm_gem_object {int /*<<< orphan*/  _resv; scalar_t__ filp; int /*<<< orphan*/  dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_resv_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_free_mmap_offset (struct drm_gem_object*) ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 

void
drm_gem_object_release(struct drm_gem_object *obj)
{
	WARN_ON(obj->dma_buf);

	if (obj->filp)
		fput(obj->filp);

	dma_resv_fini(&obj->_resv);
	drm_gem_free_mmap_offset(obj);
}