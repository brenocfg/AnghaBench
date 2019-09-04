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
struct udl_gem_object {struct page** pages; int /*<<< orphan*/  base; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page**) ; 
 int PTR_ERR (struct page**) ; 
 struct page** drm_gem_get_pages (int /*<<< orphan*/ *) ; 

int udl_gem_get_pages(struct udl_gem_object *obj)
{
	struct page **pages;

	if (obj->pages)
		return 0;

	pages = drm_gem_get_pages(&obj->base);
	if (IS_ERR(pages))
		return PTR_ERR(pages);

	obj->pages = pages;

	return 0;
}