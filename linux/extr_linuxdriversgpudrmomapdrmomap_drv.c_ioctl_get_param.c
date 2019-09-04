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
struct omap_drm_private {int /*<<< orphan*/  omaprev; } ;
struct drm_omap_param {int param; int /*<<< orphan*/  value; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EINVAL ; 
#define  OMAP_PARAM_CHIPSET_ID 128 

__attribute__((used)) static int ioctl_get_param(struct drm_device *dev, void *data,
		struct drm_file *file_priv)
{
	struct omap_drm_private *priv = dev->dev_private;
	struct drm_omap_param *args = data;

	DBG("%p: param=%llu", dev, args->param);

	switch (args->param) {
	case OMAP_PARAM_CHIPSET_ID:
		args->value = priv->omaprev;
		break;
	default:
		DBG("unknown parameter %lld", args->param);
		return -EINVAL;
	}

	return 0;
}