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
struct etnaviv_gem_object {int /*<<< orphan*/ * pages; int /*<<< orphan*/  base; int /*<<< orphan*/ * sgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_put_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  etnaviv_gem_scatterlist_unmap (struct etnaviv_gem_object*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_pages(struct etnaviv_gem_object *etnaviv_obj)
{
	if (etnaviv_obj->sgt) {
		etnaviv_gem_scatterlist_unmap(etnaviv_obj);
		sg_free_table(etnaviv_obj->sgt);
		kfree(etnaviv_obj->sgt);
		etnaviv_obj->sgt = NULL;
	}
	if (etnaviv_obj->pages) {
		drm_gem_put_pages(&etnaviv_obj->base, etnaviv_obj->pages,
				  true, false);

		etnaviv_obj->pages = NULL;
	}
}