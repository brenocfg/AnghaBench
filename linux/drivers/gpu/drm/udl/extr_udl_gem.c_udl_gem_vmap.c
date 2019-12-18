#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; TYPE_1__* import_attach; } ;
struct udl_gem_object {scalar_t__ vmapping; int /*<<< orphan*/  pages; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_SIZE ; 
 scalar_t__ dma_buf_vmap (int /*<<< orphan*/ ) ; 
 int udl_gem_get_pages (struct udl_gem_object*) ; 
 scalar_t__ vmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int udl_gem_vmap(struct udl_gem_object *obj)
{
	int page_count = obj->base.size / PAGE_SIZE;
	int ret;

	if (obj->base.import_attach) {
		obj->vmapping = dma_buf_vmap(obj->base.import_attach->dmabuf);
		if (!obj->vmapping)
			return -ENOMEM;
		return 0;
	}
		
	ret = udl_gem_get_pages(obj);
	if (ret)
		return ret;

	obj->vmapping = vmap(obj->pages, page_count, 0, PAGE_KERNEL);
	if (!obj->vmapping)
		return -ENOMEM;
	return 0;
}