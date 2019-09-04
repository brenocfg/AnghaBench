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
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {TYPE_1__* gain; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 scalar_t__ SENSOR_PO2030N ; 
 int /*<<< orphan*/  i2c_w8 (struct gspca_dev*,int*) ; 

__attribute__((used)) static void setgain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_PO2030N) {
		u8 rgain[] =		/* 15: gain */
			{0xa1, 0x6e, 0x15, 0x00, 0x40, 0x00, 0x00, 0x15};

		rgain[3] = gspca_dev->gain->val;
		i2c_w8(gspca_dev, rgain);
	}
}