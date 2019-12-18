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
struct timespec {int dummy; } ;
struct etnaviv_gpu {int dummy; } ;
struct etnaviv_gem_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int etnaviv_gpu_wait_obj_inactive (struct etnaviv_gpu*,struct etnaviv_gem_object*,struct timespec*) ; 
 struct etnaviv_gem_object* to_etnaviv_bo (struct drm_gem_object*) ; 

int etnaviv_gem_wait_bo(struct etnaviv_gpu *gpu, struct drm_gem_object *obj,
	struct timespec *timeout)
{
	struct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	return etnaviv_gpu_wait_obj_inactive(gpu, etnaviv_obj, timeout);
}