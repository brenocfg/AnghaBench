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
struct rockchip_gem_object {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rockchip_gem_object*) ; 

__attribute__((used)) static void rockchip_gem_release_object(struct rockchip_gem_object *rk_obj)
{
	drm_gem_object_release(&rk_obj->base);
	kfree(rk_obj);
}