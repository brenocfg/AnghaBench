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
struct drm_device {int /*<<< orphan*/  dev; struct fsl_dcu_drm_device* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCU_INT_STATUS ; 
 unsigned int DCU_INT_STATUS_VBLANK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_handle_vblank (struct drm_device*,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t fsl_dcu_drm_irq(int irq, void *arg)
{
	struct drm_device *dev = arg;
	struct fsl_dcu_drm_device *fsl_dev = dev->dev_private;
	unsigned int int_status;
	int ret;

	ret = regmap_read(fsl_dev->regmap, DCU_INT_STATUS, &int_status);
	if (ret) {
		dev_err(dev->dev, "read DCU_INT_STATUS failed\n");
		return IRQ_NONE;
	}

	if (int_status & DCU_INT_STATUS_VBLANK)
		drm_handle_vblank(dev, 0);

	regmap_write(fsl_dev->regmap, DCU_INT_STATUS, int_status);

	return IRQ_HANDLED;
}