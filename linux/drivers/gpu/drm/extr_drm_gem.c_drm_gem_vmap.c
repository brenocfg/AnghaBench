#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_object {TYPE_3__* dev; TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {void* (* gem_prime_vmap ) (struct drm_gem_object*) ;} ;
struct TYPE_4__ {void* (* vmap ) (struct drm_gem_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* stub1 (struct drm_gem_object*) ; 
 void* stub2 (struct drm_gem_object*) ; 

void *drm_gem_vmap(struct drm_gem_object *obj)
{
	void *vaddr;

	if (obj->funcs && obj->funcs->vmap)
		vaddr = obj->funcs->vmap(obj);
	else if (obj->dev->driver->gem_prime_vmap)
		vaddr = obj->dev->driver->gem_prime_vmap(obj);
	else
		vaddr = ERR_PTR(-EOPNOTSUPP);

	if (!vaddr)
		vaddr = ERR_PTR(-ENOMEM);

	return vaddr;
}