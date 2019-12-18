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
struct mipi_dbi {scalar_t__ reset; } ;
struct TYPE_2__ {struct device* dev; } ;
struct mipi_dbi_dev {scalar_t__ regulator; struct mipi_dbi dbi; TYPE_1__ drm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int /*<<< orphan*/  MIPI_DCS_SOFT_RESET ; 
 int mipi_dbi_command (struct mipi_dbi*,int /*<<< orphan*/ ) ; 
 scalar_t__ mipi_dbi_display_is_on (struct mipi_dbi*) ; 
 int /*<<< orphan*/  mipi_dbi_hw_reset (struct mipi_dbi*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mipi_dbi_poweron_reset_conditional(struct mipi_dbi_dev *dbidev, bool cond)
{
	struct device *dev = dbidev->drm.dev;
	struct mipi_dbi *dbi = &dbidev->dbi;
	int ret;

	if (dbidev->regulator) {
		ret = regulator_enable(dbidev->regulator);
		if (ret) {
			DRM_DEV_ERROR(dev, "Failed to enable regulator (%d)\n", ret);
			return ret;
		}
	}

	if (cond && mipi_dbi_display_is_on(dbi))
		return 1;

	mipi_dbi_hw_reset(dbi);
	ret = mipi_dbi_command(dbi, MIPI_DCS_SOFT_RESET);
	if (ret) {
		DRM_DEV_ERROR(dev, "Failed to send reset command (%d)\n", ret);
		if (dbidev->regulator)
			regulator_disable(dbidev->regulator);
		return ret;
	}

	/*
	 * If we did a hw reset, we know the controller is in Sleep mode and
	 * per MIPI DSC spec should wait 5ms after soft reset. If we didn't,
	 * we assume worst case and wait 120ms.
	 */
	if (dbi->reset)
		usleep_range(5000, 20000);
	else
		msleep(120);

	return 0;
}