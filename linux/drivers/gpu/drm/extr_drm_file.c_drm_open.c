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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;
struct drm_minor {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  open_count; TYPE_1__* anon_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_minor*) ; 
 int PTR_ERR (struct drm_minor*) ; 
 int /*<<< orphan*/  drm_close_helper (struct file*) ; 
 int drm_legacy_setup (struct drm_device*) ; 
 struct drm_minor* drm_minor_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_minor_release (struct drm_minor*) ; 
 int drm_open_helper (struct file*,struct drm_minor*) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 

int drm_open(struct inode *inode, struct file *filp)
{
	struct drm_device *dev;
	struct drm_minor *minor;
	int retcode;
	int need_setup = 0;

	minor = drm_minor_acquire(iminor(inode));
	if (IS_ERR(minor))
		return PTR_ERR(minor);

	dev = minor->dev;
	if (!dev->open_count++)
		need_setup = 1;

	/* share address_space across all char-devs of a single device */
	filp->f_mapping = dev->anon_inode->i_mapping;

	retcode = drm_open_helper(filp, minor);
	if (retcode)
		goto err_undo;
	if (need_setup) {
		retcode = drm_legacy_setup(dev);
		if (retcode) {
			drm_close_helper(filp);
			goto err_undo;
		}
	}
	return 0;

err_undo:
	dev->open_count--;
	drm_minor_release(minor);
	return retcode;
}