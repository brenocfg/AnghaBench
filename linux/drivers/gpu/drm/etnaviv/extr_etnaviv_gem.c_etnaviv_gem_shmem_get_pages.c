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
struct TYPE_2__ {struct drm_device* dev; } ;
struct etnaviv_gem_object {struct page** pages; TYPE_1__ base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page**) ; 
 int PTR_ERR (struct page**) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct page** drm_gem_get_pages (TYPE_1__*) ; 

__attribute__((used)) static int etnaviv_gem_shmem_get_pages(struct etnaviv_gem_object *etnaviv_obj)
{
	struct drm_device *dev = etnaviv_obj->base.dev;
	struct page **p = drm_gem_get_pages(&etnaviv_obj->base);

	if (IS_ERR(p)) {
		dev_dbg(dev->dev, "could not get pages: %ld\n", PTR_ERR(p));
		return PTR_ERR(p);
	}

	etnaviv_obj->pages = p;

	return 0;
}