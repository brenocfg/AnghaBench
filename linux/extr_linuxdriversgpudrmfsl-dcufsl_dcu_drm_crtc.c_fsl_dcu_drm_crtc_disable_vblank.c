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
struct fsl_dcu_drm_device {int /*<<< orphan*/  regmap; } ;
struct drm_device {struct fsl_dcu_drm_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCU_INT_MASK ; 
 unsigned int DCU_INT_MASK_VBLANK ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void fsl_dcu_drm_crtc_disable_vblank(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct fsl_dcu_drm_device *fsl_dev = dev->dev_private;
	unsigned int value;

	regmap_read(fsl_dev->regmap, DCU_INT_MASK, &value);
	value |= DCU_INT_MASK_VBLANK;
	regmap_write(fsl_dev->regmap, DCU_INT_MASK, value);
}