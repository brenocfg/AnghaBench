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
struct TYPE_2__ {int size; } ;
struct etnaviv_gem_object {scalar_t__ pages; TYPE_1__ base; scalar_t__ sgt; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  etnaviv_gem_scatterlist_unmap (struct etnaviv_gem_object*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  kvfree (scalar_t__) ; 
 int /*<<< orphan*/  release_pages (scalar_t__,int) ; 
 int /*<<< orphan*/  sg_free_table (scalar_t__) ; 

__attribute__((used)) static void etnaviv_gem_userptr_release(struct etnaviv_gem_object *etnaviv_obj)
{
	if (etnaviv_obj->sgt) {
		etnaviv_gem_scatterlist_unmap(etnaviv_obj);
		sg_free_table(etnaviv_obj->sgt);
		kfree(etnaviv_obj->sgt);
	}
	if (etnaviv_obj->pages) {
		int npages = etnaviv_obj->base.size >> PAGE_SHIFT;

		release_pages(etnaviv_obj->pages, npages);
		kvfree(etnaviv_obj->pages);
	}
}