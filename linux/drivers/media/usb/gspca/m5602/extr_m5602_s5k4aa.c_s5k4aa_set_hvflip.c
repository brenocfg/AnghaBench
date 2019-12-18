#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sd {TYPE_2__* vflip; TYPE_1__* hflip; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_4__ {int val; } ;
struct TYPE_3__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  S5K4AA_COLSTART_LO ; 
 int /*<<< orphan*/  S5K4AA_PAGE_MAP ; 
 int S5K4AA_PAGE_MAP_2 ; 
 int /*<<< orphan*/  S5K4AA_READ_MODE ; 
 int /*<<< orphan*/  S5K4AA_ROWSTART_LO ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int) ; 
 int m5602_read_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  s5k4aa_vflip_dmi_table ; 

__attribute__((used)) static int s5k4aa_set_hvflip(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	int err;
	int hflip = sd->hflip->val;
	int vflip = sd->vflip->val;

	gspca_dbg(gspca_dev, D_CONF, "Set hvflip %d %d\n", hflip, vflip);
	err = m5602_write_sensor(sd, S5K4AA_PAGE_MAP, &data, 1);
	if (err < 0)
		return err;

	err = m5602_read_sensor(sd, S5K4AA_READ_MODE, &data, 1);
	if (err < 0)
		return err;

	if (dmi_check_system(s5k4aa_vflip_dmi_table)) {
		hflip = !hflip;
		vflip = !vflip;
	}

	data = (data & 0x7f) | (vflip << 7) | (hflip << 6);
	err = m5602_write_sensor(sd, S5K4AA_READ_MODE, &data, 1);
	if (err < 0)
		return err;

	err = m5602_read_sensor(sd, S5K4AA_COLSTART_LO, &data, 1);
	if (err < 0)
		return err;
	if (hflip)
		data &= 0xfe;
	else
		data |= 0x01;
	err = m5602_write_sensor(sd, S5K4AA_COLSTART_LO, &data, 1);
	if (err < 0)
		return err;

	err = m5602_read_sensor(sd, S5K4AA_ROWSTART_LO, &data, 1);
	if (err < 0)
		return err;
	if (vflip)
		data &= 0xfe;
	else
		data |= 0x01;
	err = m5602_write_sensor(sd, S5K4AA_ROWSTART_LO, &data, 1);
	if (err < 0)
		return err;

	return 0;
}