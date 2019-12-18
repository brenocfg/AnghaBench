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
struct xen_gem_object {int /*<<< orphan*/  base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct xen_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kfree (struct xen_gem_object*) ; 
 struct xen_gem_object* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xen_gem_object *gem_create_obj(struct drm_device *dev,
					     size_t size)
{
	struct xen_gem_object *xen_obj;
	int ret;

	xen_obj = kzalloc(sizeof(*xen_obj), GFP_KERNEL);
	if (!xen_obj)
		return ERR_PTR(-ENOMEM);

	ret = drm_gem_object_init(dev, &xen_obj->base, size);
	if (ret < 0) {
		kfree(xen_obj);
		return ERR_PTR(ret);
	}

	return xen_obj;
}