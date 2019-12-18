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
struct ltdc_device {int /*<<< orphan*/  pixel_clk; } ;
struct drm_device {struct ltdc_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

int ltdc_resume(struct drm_device *ddev)
{
	struct ltdc_device *ldev = ddev->dev_private;
	int ret;

	DRM_DEBUG_DRIVER("\n");

	ret = clk_prepare_enable(ldev->pixel_clk);
	if (ret) {
		DRM_ERROR("failed to enable pixel clock (%d)\n", ret);
		return ret;
	}

	return 0;
}