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
struct fsl_dcu_drm_device {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_crtc; } ;
struct drm_device {struct fsl_dcu_drm_device* dev_private; int /*<<< orphan*/  dev; TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int drm_irq_install (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int fsl_dcu_drm_modeset_init (struct fsl_dcu_drm_device*) ; 
 int legacyfb_depth ; 

__attribute__((used)) static int fsl_dcu_load(struct drm_device *dev, unsigned long flags)
{
	struct fsl_dcu_drm_device *fsl_dev = dev->dev_private;
	int ret;

	ret = fsl_dcu_drm_modeset_init(fsl_dev);
	if (ret < 0) {
		dev_err(dev->dev, "failed to initialize mode setting\n");
		return ret;
	}

	ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
	if (ret < 0) {
		dev_err(dev->dev, "failed to initialize vblank\n");
		goto done;
	}

	ret = drm_irq_install(dev, fsl_dev->irq);
	if (ret < 0) {
		dev_err(dev->dev, "failed to install IRQ handler\n");
		goto done;
	}

	if (legacyfb_depth != 16 && legacyfb_depth != 24 &&
	    legacyfb_depth != 32) {
		dev_warn(dev->dev,
			"Invalid legacyfb_depth.  Defaulting to 24bpp\n");
		legacyfb_depth = 24;
	}

	return 0;
done:
	drm_kms_helper_poll_fini(dev);

	drm_mode_config_cleanup(dev);
	drm_irq_uninstall(dev);
	dev->dev_private = NULL;

	return ret;
}