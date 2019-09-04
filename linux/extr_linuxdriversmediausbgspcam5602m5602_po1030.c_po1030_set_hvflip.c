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
 int /*<<< orphan*/  PO1030_CONTROL2 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int) ; 
 int m5602_read_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int po1030_set_hvflip(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 i2c_data;
	int err;

	gspca_dbg(gspca_dev, D_CONF, "Set hvflip %d %d\n",
		  sd->hflip->val, sd->vflip->val);
	err = m5602_read_sensor(sd, PO1030_CONTROL2, &i2c_data, 1);
	if (err < 0)
		return err;

	i2c_data = (0x3f & i2c_data) | (sd->hflip->val << 7) |
		   (sd->vflip->val << 6);

	err = m5602_write_sensor(sd, PO1030_CONTROL2,
				 &i2c_data, 1);

	return err;
}