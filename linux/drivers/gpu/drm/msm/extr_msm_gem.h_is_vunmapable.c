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
struct msm_gem_object {scalar_t__ vmap_count; scalar_t__ vaddr; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_vunmapable(struct msm_gem_object *msm_obj)
{
	return (msm_obj->vmap_count == 0) && msm_obj->vaddr;
}