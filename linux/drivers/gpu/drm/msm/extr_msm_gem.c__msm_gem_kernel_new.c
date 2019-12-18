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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_gem_address_space {int dummy; } ;
typedef  void drm_gem_object ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 void* ERR_CAST (void*) ; 
 void* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* _msm_gem_new (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_gem_object_put (void*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (void*) ; 
 int msm_gem_get_and_pin_iova (void*,struct msm_gem_address_space*,int /*<<< orphan*/ *) ; 
 void* msm_gem_get_vaddr (void*) ; 
 int /*<<< orphan*/  msm_gem_unpin_iova (void*,struct msm_gem_address_space*) ; 

__attribute__((used)) static void *_msm_gem_kernel_new(struct drm_device *dev, uint32_t size,
		uint32_t flags, struct msm_gem_address_space *aspace,
		struct drm_gem_object **bo, uint64_t *iova, bool locked)
{
	void *vaddr;
	struct drm_gem_object *obj = _msm_gem_new(dev, size, flags, locked);
	int ret;

	if (IS_ERR(obj))
		return ERR_CAST(obj);

	if (iova) {
		ret = msm_gem_get_and_pin_iova(obj, aspace, iova);
		if (ret)
			goto err;
	}

	vaddr = msm_gem_get_vaddr(obj);
	if (IS_ERR(vaddr)) {
		msm_gem_unpin_iova(obj, aspace);
		ret = PTR_ERR(vaddr);
		goto err;
	}

	if (bo)
		*bo = obj;

	return vaddr;
err:
	if (locked)
		drm_gem_object_put(obj);
	else
		drm_gem_object_put_unlocked(obj);

	return ERR_PTR(ret);

}