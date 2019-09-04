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
struct sd {int sensor; int do_ctrl; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; int usb_err; TYPE_2__ cam; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Creative_live_motion ; 
#define  SENSOR_ICX098BQ 130 
#define  SENSOR_LZ24BP 129 
#define  SENSOR_MI0360 128 
 int SENSOR_MT9V111 ; 
 int /*<<< orphan*/  SQ930_CTRL_CAP_STOP ; 
 int SQ930_GPIO_DFL_LED ; 
 int SQ930_GPIO_EXTRA2 ; 
 int SQ930_GPIO_RSTBAR ; 
 int /*<<< orphan*/  bridge_init (struct sd*) ; 
 int /*<<< orphan*/  global_init (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set (struct sd*,int,int) ; 
 int /*<<< orphan*/  i2c_write (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icx098bq_start_0 ; 
 int /*<<< orphan*/  icx098bq_start_1 ; 
 int /*<<< orphan*/  icx098bq_start_2 ; 
 int /*<<< orphan*/  lz24bp_ppl (struct sd*,int) ; 
 int /*<<< orphan*/  lz24bp_start_0 ; 
 int /*<<< orphan*/  lz24bp_start_1_clm ; 
 int /*<<< orphan*/  lz24bp_start_1_gen ; 
 int /*<<< orphan*/  lz24bp_start_2 ; 
 int /*<<< orphan*/  mi0360_init_23 ; 
 int /*<<< orphan*/  mi0360_init_24 ; 
 int /*<<< orphan*/  mi0360_init_25 ; 
 int /*<<< orphan*/  mi0360_start_0 ; 
 int /*<<< orphan*/  mi0360_start_1 ; 
 int /*<<< orphan*/  mi0360_start_2 ; 
 int /*<<< orphan*/  mi0360_start_3 ; 
 int /*<<< orphan*/  mi0360_start_4 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mt9v111_init_0 ; 
 int /*<<< orphan*/  mt9v111_init_1 ; 
 int /*<<< orphan*/  mt9v111_init_2 ; 
 int /*<<< orphan*/  mt9v111_init_3 ; 
 int /*<<< orphan*/  mt9v111_init_4 ; 
 int /*<<< orphan*/  mt9v111_start_1 ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_start (struct gspca_dev*) ; 
 int /*<<< orphan*/  send_stop (struct gspca_dev*) ; 
 int /*<<< orphan*/  ucbus_write (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int mode;

	bridge_init(sd);
	global_init(sd, 0);
	msleep(100);

	switch (sd->sensor) {
	case SENSOR_ICX098BQ:
		ucbus_write(gspca_dev, icx098bq_start_0,
				ARRAY_SIZE(icx098bq_start_0),
				8);
		ucbus_write(gspca_dev, icx098bq_start_1,
				ARRAY_SIZE(icx098bq_start_1),
				5);
		ucbus_write(gspca_dev, icx098bq_start_2,
				ARRAY_SIZE(icx098bq_start_2),
				6);
		msleep(50);

		/* 1st start */
		send_start(gspca_dev);
		gpio_set(sd, SQ930_GPIO_EXTRA2 | SQ930_GPIO_RSTBAR, 0x00ff);
		msleep(70);
		reg_w(gspca_dev, SQ930_CTRL_CAP_STOP, 0x0000);
		gpio_set(sd, 0x7f, 0x00ff);

		/* 2nd start */
		send_start(gspca_dev);
		gpio_set(sd, SQ930_GPIO_EXTRA2 | SQ930_GPIO_RSTBAR, 0x00ff);
		goto out;
	case SENSOR_LZ24BP:
		ucbus_write(gspca_dev, lz24bp_start_0,
				ARRAY_SIZE(lz24bp_start_0),
				8);
		if (sd->type != Creative_live_motion)
			ucbus_write(gspca_dev, lz24bp_start_1_gen,
					ARRAY_SIZE(lz24bp_start_1_gen),
					5);
		else
			ucbus_write(gspca_dev, lz24bp_start_1_clm,
					ARRAY_SIZE(lz24bp_start_1_clm),
					5);
		ucbus_write(gspca_dev, lz24bp_start_2,
				ARRAY_SIZE(lz24bp_start_2),
				6);
		mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
		lz24bp_ppl(sd, mode == 1 ? 0x0564 : 0x0310);
		msleep(10);
		break;
	case SENSOR_MI0360:
		ucbus_write(gspca_dev, mi0360_start_0,
				ARRAY_SIZE(mi0360_start_0),
				8);
		i2c_write(sd, mi0360_init_23,
				ARRAY_SIZE(mi0360_init_23));
		i2c_write(sd, mi0360_init_24,
				ARRAY_SIZE(mi0360_init_24));
		i2c_write(sd, mi0360_init_25,
				ARRAY_SIZE(mi0360_init_25));
		ucbus_write(gspca_dev, mi0360_start_1,
				ARRAY_SIZE(mi0360_start_1),
				5);
		i2c_write(sd, mi0360_start_2,
				ARRAY_SIZE(mi0360_start_2));
		i2c_write(sd, mi0360_start_3,
				ARRAY_SIZE(mi0360_start_3));

		/* 1st start */
		send_start(gspca_dev);
		msleep(60);
		send_stop(gspca_dev);

		i2c_write(sd,
			mi0360_start_4, ARRAY_SIZE(mi0360_start_4));
		break;
	default:
/*	case SENSOR_MT9V111: */
		ucbus_write(gspca_dev, mi0360_start_0,
				ARRAY_SIZE(mi0360_start_0),
				8);
		i2c_write(sd, mt9v111_init_0,
				ARRAY_SIZE(mt9v111_init_0));
		i2c_write(sd, mt9v111_init_1,
				ARRAY_SIZE(mt9v111_init_1));
		i2c_write(sd, mt9v111_init_2,
				ARRAY_SIZE(mt9v111_init_2));
		ucbus_write(gspca_dev, mt9v111_start_1,
				ARRAY_SIZE(mt9v111_start_1),
				5);
		i2c_write(sd, mt9v111_init_3,
				ARRAY_SIZE(mt9v111_init_3));
		i2c_write(sd, mt9v111_init_4,
				ARRAY_SIZE(mt9v111_init_4));
		break;
	}

	send_start(gspca_dev);
out:
	msleep(1000);

	if (sd->sensor == SENSOR_MT9V111)
		gpio_set(sd, SQ930_GPIO_DFL_LED, SQ930_GPIO_DFL_LED);

	sd->do_ctrl = 1;	/* set the exposure */

	return gspca_dev->usb_err;
}