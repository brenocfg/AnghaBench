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
struct radeon_device {int /*<<< orphan*/  exclusive_lock; } ;
struct radeon_bo {int /*<<< orphan*/  rdev; } ;
struct drm_radeon_gem_set_domain {int /*<<< orphan*/  write_domain; int /*<<< orphan*/  read_domains; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int radeon_gem_handle_lockup (int /*<<< orphan*/ ,int) ; 
 int radeon_gem_set_domain (struct drm_gem_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int radeon_gem_set_domain_ioctl(struct drm_device *dev, void *data,
				struct drm_file *filp)
{
	/* transition the BO to a domain -
	 * just validate the BO into a certain domain */
	struct radeon_device *rdev = dev->dev_private;
	struct drm_radeon_gem_set_domain *args = data;
	struct drm_gem_object *gobj;
	struct radeon_bo *robj;
	int r;

	/* for now if someone requests domain CPU -
	 * just make sure the buffer is finished with */
	down_read(&rdev->exclusive_lock);

	/* just do a BO wait for now */
	gobj = drm_gem_object_lookup(filp, args->handle);
	if (gobj == NULL) {
		up_read(&rdev->exclusive_lock);
		return -ENOENT;
	}
	robj = gem_to_radeon_bo(gobj);

	r = radeon_gem_set_domain(gobj, args->read_domains, args->write_domain);

	drm_gem_object_put_unlocked(gobj);
	up_read(&rdev->exclusive_lock);
	r = radeon_gem_handle_lockup(robj->rdev, r);
	return r;
}