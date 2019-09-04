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
typedef  int ssize_t ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  MIPI_DCS_GET_POWER_MODE ; 
 int mipi_dsi_dcs_read (struct mipi_dsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int mipi_dsi_dcs_get_power_mode(struct mipi_dsi_device *dsi, u8 *mode)
{
	ssize_t err;

	err = mipi_dsi_dcs_read(dsi, MIPI_DCS_GET_POWER_MODE, mode,
				sizeof(*mode));
	if (err <= 0) {
		if (err == 0)
			err = -ENODATA;

		return err;
	}

	return 0;
}