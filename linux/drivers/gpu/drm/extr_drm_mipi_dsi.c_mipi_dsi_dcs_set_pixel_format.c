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
typedef  int /*<<< orphan*/  u8 ;
struct mipi_dsi_device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_SET_PIXEL_FORMAT ; 
 scalar_t__ mipi_dsi_dcs_write (struct mipi_dsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int mipi_dsi_dcs_set_pixel_format(struct mipi_dsi_device *dsi, u8 format)
{
	ssize_t err;

	err = mipi_dsi_dcs_write(dsi, MIPI_DCS_SET_PIXEL_FORMAT, &format,
				 sizeof(format));
	if (err < 0)
		return err;

	return 0;
}