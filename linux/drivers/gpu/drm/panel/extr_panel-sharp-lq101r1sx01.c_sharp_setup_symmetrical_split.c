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
struct mipi_dsi_device {int /*<<< orphan*/  dev; } ;
struct drm_display_mode {int hdisplay; scalar_t__ vdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mipi_dsi_dcs_set_column_address (struct mipi_dsi_device*,int,int) ; 
 int mipi_dsi_dcs_set_page_address (struct mipi_dsi_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sharp_setup_symmetrical_split(struct mipi_dsi_device *left,
					 struct mipi_dsi_device *right,
					 const struct drm_display_mode *mode)
{
	int err;

	err = mipi_dsi_dcs_set_column_address(left, 0, mode->hdisplay / 2 - 1);
	if (err < 0) {
		dev_err(&left->dev, "failed to set column address: %d\n", err);
		return err;
	}

	err = mipi_dsi_dcs_set_page_address(left, 0, mode->vdisplay - 1);
	if (err < 0) {
		dev_err(&left->dev, "failed to set page address: %d\n", err);
		return err;
	}

	err = mipi_dsi_dcs_set_column_address(right, mode->hdisplay / 2,
					      mode->hdisplay - 1);
	if (err < 0) {
		dev_err(&right->dev, "failed to set column address: %d\n", err);
		return err;
	}

	err = mipi_dsi_dcs_set_page_address(right, 0, mode->vdisplay - 1);
	if (err < 0) {
		dev_err(&right->dev, "failed to set page address: %d\n", err);
		return err;
	}

	return 0;
}