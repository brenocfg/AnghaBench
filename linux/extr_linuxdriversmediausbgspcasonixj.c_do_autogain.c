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
typedef  int u8 ;
struct sd {scalar_t__ ag_cnt; int sensor; int exposure; int /*<<< orphan*/  avg_lum; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ AG_CNT_START ; 
 int /*<<< orphan*/  D_FRAM ; 
#define  SENSOR_GC0307 131 
#define  SENSOR_HV7131R 130 
#define  SENSOR_MT9V111 129 
#define  SENSOR_OM6802 128 
 int SENSOR_PO2030N ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 void* expo_adjust (struct gspca_dev*,unsigned int) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gspca_expo_autogain (struct gspca_dev*,int,int,int,int,int) ; 
 int /*<<< orphan*/  setredblue (struct gspca_dev*) ; 

__attribute__((used)) static void do_autogain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int delta;
	int expotimes;
	u8 luma_mean = 130;
	u8 luma_delta = 20;

	/* Thanks S., without your advice, autobright should not work :) */
	if (sd->ag_cnt < 0)
		return;
	if (--sd->ag_cnt >= 0)
		return;
	sd->ag_cnt = AG_CNT_START;

	delta = atomic_read(&sd->avg_lum);
	gspca_dbg(gspca_dev, D_FRAM, "mean lum %d\n", delta);

	if (sd->sensor == SENSOR_PO2030N) {
		gspca_expo_autogain(gspca_dev, delta, luma_mean, luma_delta,
					15, 1024);
		return;
	}

	if (delta < luma_mean - luma_delta ||
	    delta > luma_mean + luma_delta) {
		switch (sd->sensor) {
		case SENSOR_GC0307:
			expotimes = sd->exposure;
			expotimes += (luma_mean - delta) >> 6;
			if (expotimes < 0)
				expotimes = 0;
			sd->exposure = expo_adjust(gspca_dev,
						   (unsigned int) expotimes);
			break;
		case SENSOR_HV7131R:
			expotimes = sd->exposure >> 8;
			expotimes += (luma_mean - delta) >> 4;
			if (expotimes < 0)
				expotimes = 0;
			sd->exposure = expo_adjust(gspca_dev,
					(unsigned int) (expotimes << 8));
			break;
		case SENSOR_OM6802:
		case SENSOR_MT9V111:
			expotimes = sd->exposure;
			expotimes += (luma_mean - delta) >> 2;
			if (expotimes < 0)
				expotimes = 0;
			sd->exposure = expo_adjust(gspca_dev,
						   (unsigned int) expotimes);
			setredblue(gspca_dev);
			break;
		default:
/*		case SENSOR_MO4000: */
/*		case SENSOR_MI0360: */
/*		case SENSOR_MI0360B: */
			expotimes = sd->exposure;
			expotimes += (luma_mean - delta) >> 6;
			if (expotimes < 0)
				expotimes = 0;
			sd->exposure = expo_adjust(gspca_dev,
						   (unsigned int) expotimes);
			setredblue(gspca_dev);
			break;
		}
	}
}