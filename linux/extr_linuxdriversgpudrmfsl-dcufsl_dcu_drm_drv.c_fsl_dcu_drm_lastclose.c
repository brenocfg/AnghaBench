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
struct fsl_dcu_drm_device {int /*<<< orphan*/  fbdev; } ;
struct drm_device {struct fsl_dcu_drm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fbdev_cma_restore_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_dcu_drm_lastclose(struct drm_device *dev)
{
	struct fsl_dcu_drm_device *fsl_dev = dev->dev_private;

	drm_fbdev_cma_restore_mode(fsl_dev->fbdev);
}