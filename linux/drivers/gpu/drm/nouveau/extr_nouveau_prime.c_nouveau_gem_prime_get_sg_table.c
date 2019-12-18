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
struct sg_table {int dummy; } ;
struct TYPE_4__ {int num_pages; TYPE_1__* ttm; } ;
struct nouveau_bo {TYPE_2__ bo; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 struct sg_table* drm_prime_pages_to_sg (int /*<<< orphan*/ ,int) ; 
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 

struct sg_table *nouveau_gem_prime_get_sg_table(struct drm_gem_object *obj)
{
	struct nouveau_bo *nvbo = nouveau_gem_object(obj);
	int npages = nvbo->bo.num_pages;

	return drm_prime_pages_to_sg(nvbo->bo.ttm->pages, npages);
}