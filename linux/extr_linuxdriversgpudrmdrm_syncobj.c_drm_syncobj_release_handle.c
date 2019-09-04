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
struct drm_syncobj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 

__attribute__((used)) static int
drm_syncobj_release_handle(int id, void *ptr, void *data)
{
	struct drm_syncobj *syncobj = ptr;

	drm_syncobj_put(syncobj);
	return 0;
}