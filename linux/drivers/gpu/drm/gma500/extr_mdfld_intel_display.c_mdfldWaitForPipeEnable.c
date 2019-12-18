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
struct psb_offset {int /*<<< orphan*/  conf; } ;
struct drm_psb_private {struct psb_offset* regmap; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int COUNT_MAX ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int PIPEACONF_PIPE_STATE ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_wait_for_vblank (struct drm_device*) ; 

void mdfldWaitForPipeEnable(struct drm_device *dev, int pipe)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	const struct psb_offset *map = &dev_priv->regmap[pipe];
	int count, temp;

	switch (pipe) {
	case 0:
	case 1:
	case 2:
		break;
	default:
		DRM_ERROR("Illegal Pipe Number.\n");
		return;
	}

	/* FIXME JLIU7_PO */
	gma_wait_for_vblank(dev);
	return;

	/* Wait for for the pipe enable to take effect. */
	for (count = 0; count < COUNT_MAX; count++) {
		temp = REG_READ(map->conf);
		if (temp & PIPEACONF_PIPE_STATE)
			break;
	}
}