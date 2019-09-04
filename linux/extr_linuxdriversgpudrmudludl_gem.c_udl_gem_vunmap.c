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
struct TYPE_4__ {TYPE_1__* import_attach; } ;
struct udl_gem_object {int /*<<< orphan*/  vmapping; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_buf_vunmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udl_gem_put_pages (struct udl_gem_object*) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

void udl_gem_vunmap(struct udl_gem_object *obj)
{
	if (obj->base.import_attach) {
		dma_buf_vunmap(obj->base.import_attach->dmabuf, obj->vmapping);
		return;
	}

	vunmap(obj->vmapping);

	udl_gem_put_pages(obj);
}