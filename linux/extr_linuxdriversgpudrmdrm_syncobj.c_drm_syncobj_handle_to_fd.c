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
typedef  int /*<<< orphan*/  u32 ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,int /*<<< orphan*/ ) ; 
 int drm_syncobj_get_fd (struct drm_syncobj*,int*) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 

__attribute__((used)) static int drm_syncobj_handle_to_fd(struct drm_file *file_private,
				    u32 handle, int *p_fd)
{
	struct drm_syncobj *syncobj = drm_syncobj_find(file_private, handle);
	int ret;

	if (!syncobj)
		return -EINVAL;

	ret = drm_syncobj_get_fd(syncobj, p_fd);
	drm_syncobj_put(syncobj);
	return ret;
}