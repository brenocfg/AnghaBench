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
typedef  int u8 ;
struct sd {int sensor; int ag_cnt; int /*<<< orphan*/  gspca_dev; } ;
struct gspca_dev {TYPE_1__* autogain; } ;
struct TYPE_2__ {scalar_t__ val; } ;

/* Variables and functions */
 int AG_CNT_START ; 
#define  SENSOR_OV7630 129 
#define  SENSOR_OV7648 128 
 int /*<<< orphan*/  i2c_w1 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void setautogain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->sensor) {
	case SENSOR_OV7630:
	case SENSOR_OV7648: {
		u8 comb;

		if (sd->sensor == SENSOR_OV7630)
			comb = 0xc0;
		else
			comb = 0xa0;
		if (gspca_dev->autogain->val)
			comb |= 0x03;
		i2c_w1(&sd->gspca_dev, 0x13, comb);
		return;
	    }
	}
	if (gspca_dev->autogain->val)
		sd->ag_cnt = AG_CNT_START;
	else
		sd->ag_cnt = -1;
}