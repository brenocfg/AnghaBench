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
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_object {TYPE_1__* dev; } ;
struct drm_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  object_name_lock; } ;

/* Variables and functions */
 int drm_gem_handle_create_tail (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

int drm_gem_handle_create(struct drm_file *file_priv,
			  struct drm_gem_object *obj,
			  u32 *handlep)
{
	mutex_lock(&obj->dev->object_name_lock);

	return drm_gem_handle_create_tail(file_priv, obj, handlep);
}