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
struct drm_gem_object {int /*<<< orphan*/ * dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_buf_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_gem_object_exported_dma_buf_free(struct drm_gem_object *obj)
{
	/* Unbreak the reference cycle if we have an exported dma_buf. */
	if (obj->dma_buf) {
		dma_buf_put(obj->dma_buf);
		obj->dma_buf = NULL;
	}
}