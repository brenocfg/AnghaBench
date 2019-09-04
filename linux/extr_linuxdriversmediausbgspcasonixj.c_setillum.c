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
struct sd {int sensor; TYPE_1__* illum; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
#define  SENSOR_ADCM1700 129 
#define  SENSOR_MT9V111 128 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setillum(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->sensor) {
	case SENSOR_ADCM1700:
		reg_w1(gspca_dev, 0x02,				/* gpio */
			sd->illum->val ? 0x64 : 0x60);
		break;
	case SENSOR_MT9V111:
		reg_w1(gspca_dev, 0x02,
			sd->illum->val ? 0x77 : 0x74);
/* should have been: */
/*						0x55 : 0x54);	* 370i */
/*						0x66 : 0x64);	* Clip */
		break;
	}
}