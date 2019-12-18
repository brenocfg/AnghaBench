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
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  objects_lookup (struct drm_file*,int /*<<< orphan*/ *,int,struct drm_gem_object**) ; 

struct drm_gem_object *
drm_gem_object_lookup(struct drm_file *filp, u32 handle)
{
	struct drm_gem_object *obj = NULL;

	objects_lookup(filp, &handle, 1, &obj);
	return obj;
}