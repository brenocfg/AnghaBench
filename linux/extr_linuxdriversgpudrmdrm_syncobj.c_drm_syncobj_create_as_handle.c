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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int drm_syncobj_create (struct drm_syncobj**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_syncobj_get_handle (struct drm_file*,struct drm_syncobj*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 

__attribute__((used)) static int drm_syncobj_create_as_handle(struct drm_file *file_private,
					u32 *handle, uint32_t flags)
{
	int ret;
	struct drm_syncobj *syncobj;

	ret = drm_syncobj_create(&syncobj, flags, NULL);
	if (ret)
		return ret;

	ret = drm_syncobj_get_handle(file_private, syncobj, handle);
	drm_syncobj_put(syncobj);
	return ret;
}