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
struct drm_gem_object {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_heap; } ;

/* Variables and functions */
 int EINVAL ; 
 int drm_gem_shmem_pin (struct drm_gem_object*) ; 
 TYPE_1__* to_panfrost_bo (struct drm_gem_object*) ; 

__attribute__((used)) static int panfrost_gem_pin(struct drm_gem_object *obj)
{
	if (to_panfrost_bo(obj)->is_heap)
		return -EINVAL;

	return drm_gem_shmem_pin(obj);
}