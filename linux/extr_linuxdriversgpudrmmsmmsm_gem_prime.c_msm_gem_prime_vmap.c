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
 void* msm_gem_get_vaddr (struct drm_gem_object*) ; 

void *msm_gem_prime_vmap(struct drm_gem_object *obj)
{
	return msm_gem_get_vaddr(obj);
}