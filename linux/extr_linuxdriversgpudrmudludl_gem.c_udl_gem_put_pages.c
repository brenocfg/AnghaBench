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
struct TYPE_2__ {scalar_t__ import_attach; } ;
struct udl_gem_object {int /*<<< orphan*/ * pages; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_put_pages (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

void udl_gem_put_pages(struct udl_gem_object *obj)
{
	if (obj->base.import_attach) {
		kvfree(obj->pages);
		obj->pages = NULL;
		return;
	}

	drm_gem_put_pages(&obj->base, obj->pages, false, false);
	obj->pages = NULL;
}