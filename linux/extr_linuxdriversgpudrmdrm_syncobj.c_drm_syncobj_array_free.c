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
typedef  size_t uint32_t ;
struct drm_syncobj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 int /*<<< orphan*/  kfree (struct drm_syncobj**) ; 

__attribute__((used)) static void drm_syncobj_array_free(struct drm_syncobj **syncobjs,
				   uint32_t count)
{
	uint32_t i;
	for (i = 0; i < count; i++)
		drm_syncobj_put(syncobjs[i]);
	kfree(syncobjs);
}