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
struct rockchip_gem_object {int /*<<< orphan*/  pages; int /*<<< orphan*/  base; int /*<<< orphan*/  sgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_put_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rockchip_gem_put_pages(struct rockchip_gem_object *rk_obj)
{
	sg_free_table(rk_obj->sgt);
	kfree(rk_obj->sgt);
	drm_gem_put_pages(&rk_obj->base, rk_obj->pages, true, true);
}