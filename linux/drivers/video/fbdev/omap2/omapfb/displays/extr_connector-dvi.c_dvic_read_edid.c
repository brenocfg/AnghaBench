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
typedef  scalar_t__ u8 ;
struct panel_drv_data {int /*<<< orphan*/  i2c_adapter; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int ENODEV ; 
 int dvic_ddc_read (int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int min (int,int) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int dvic_read_edid(struct omap_dss_device *dssdev,
		u8 *edid, int len)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	int r, l, bytes_read;

	if (!ddata->i2c_adapter)
		return -ENODEV;

	l = min(EDID_LENGTH, len);
	r = dvic_ddc_read(ddata->i2c_adapter, edid, l, 0);
	if (r)
		return r;

	bytes_read = l;

	/* if there are extensions, read second block */
	if (len > EDID_LENGTH && edid[0x7e] > 0) {
		l = min(EDID_LENGTH, len - EDID_LENGTH);

		r = dvic_ddc_read(ddata->i2c_adapter, edid + EDID_LENGTH,
				l, EDID_LENGTH);
		if (r)
			return r;

		bytes_read += l;
	}

	return bytes_read;
}