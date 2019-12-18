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
struct file {struct drm_file* private_data; } ;
struct drm_psb_private {int rpm_enabled; scalar_t__ is_lvds_on; } ;
struct drm_file {TYPE_1__* minor; } ;
struct drm_device {TYPE_2__* pdev; struct drm_psb_private* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct drm_device* dev; } ;

/* Variables and functions */
 long drm_ioctl (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long psb_unlocked_ioctl(struct file *filp, unsigned int cmd,
			       unsigned long arg)
{
	struct drm_file *file_priv = filp->private_data;
	struct drm_device *dev = file_priv->minor->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	static unsigned int runtime_allowed;

	if (runtime_allowed == 1 && dev_priv->is_lvds_on) {
		runtime_allowed++;
		pm_runtime_allow(&dev->pdev->dev);
		dev_priv->rpm_enabled = 1;
	}
	return drm_ioctl(filp, cmd, arg);
	/* FIXME: do we need to wrap the other side of this */
}