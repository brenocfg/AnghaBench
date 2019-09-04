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
struct page {int dummy; } ;
struct TYPE_2__ {int size; } ;
struct etnaviv_gem_object {TYPE_1__ base; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page**) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_MAP ; 
 struct page** etnaviv_gem_get_pages (struct etnaviv_gem_object*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 void* vmap (struct page**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *etnaviv_gem_vmap_impl(struct etnaviv_gem_object *obj)
{
	struct page **pages;

	lockdep_assert_held(&obj->lock);

	pages = etnaviv_gem_get_pages(obj);
	if (IS_ERR(pages))
		return NULL;

	return vmap(pages, obj->base.size >> PAGE_SHIFT,
			VM_MAP, pgprot_writecombine(PAGE_KERNEL));
}