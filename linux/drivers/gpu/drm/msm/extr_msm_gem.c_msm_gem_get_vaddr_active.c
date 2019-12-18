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
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __MSM_MADV_PURGED ; 
 void* get_vaddr (struct drm_gem_object*,int /*<<< orphan*/ ) ; 

void *msm_gem_get_vaddr_active(struct drm_gem_object *obj)
{
	return get_vaddr(obj, __MSM_MADV_PURGED);
}