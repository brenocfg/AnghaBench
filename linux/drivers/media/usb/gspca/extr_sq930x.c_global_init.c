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
struct sd {int sensor; int /*<<< orphan*/  gspca_dev; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Creative_live_motion ; 
#define  SENSOR_ICX098BQ 130 
#define  SENSOR_LZ24BP 129 
#define  SENSOR_MI0360 128 
 int SQ930_GPIO_EXTRA1 ; 
 int SQ930_GPIO_EXTRA2 ; 
 int /*<<< orphan*/  gpio_init (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set (struct sd*,int,int) ; 
 int /*<<< orphan*/  icx098bq_start_0 ; 
 int /*<<< orphan*/  lz24bp_start_0 ; 
 int /*<<< orphan*/  mi0360_start_0 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mt9v111_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* sensor_tb ; 
 int /*<<< orphan*/  ucbus_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void global_init(struct sd *sd, int first_time)
{
	switch (sd->sensor) {
	case SENSOR_ICX098BQ:
		if (first_time)
			ucbus_write(&sd->gspca_dev,
					icx098bq_start_0,
					8, 8);
		gpio_init(sd, sensor_tb[sd->sensor].gpio);
		break;
	case SENSOR_LZ24BP:
		if (sd->type != Creative_live_motion)
			gpio_set(sd, SQ930_GPIO_EXTRA1, 0x00ff);
		else
			gpio_set(sd, 0, 0x00ff);
		msleep(50);
		if (first_time)
			ucbus_write(&sd->gspca_dev,
					lz24bp_start_0,
					8, 8);
		gpio_init(sd, sensor_tb[sd->sensor].gpio);
		break;
	case SENSOR_MI0360:
		if (first_time)
			ucbus_write(&sd->gspca_dev,
					mi0360_start_0,
					ARRAY_SIZE(mi0360_start_0),
					8);
		gpio_init(sd, sensor_tb[sd->sensor].gpio);
		gpio_set(sd, SQ930_GPIO_EXTRA2, SQ930_GPIO_EXTRA2);
		break;
	default:
/*	case SENSOR_MT9V111: */
		if (first_time)
			mt9v111_init(&sd->gspca_dev);
		else
			gpio_init(sd, sensor_tb[sd->sensor].gpio);
		break;
	}
}