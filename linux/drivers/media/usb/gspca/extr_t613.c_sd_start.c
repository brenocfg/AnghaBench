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
struct sd {int sensor; int /*<<< orphan*/  freq; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; TYPE_2__ cam; } ;
struct additional_sensor_data {int* stream; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int**) ; 
#define  SENSOR_OM6802 129 
#define  SENSOR_TAS5130A 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  om6802_sensor_init (struct gspca_dev*) ; 
 int /*<<< orphan*/  poll_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int*,int) ; 
 int /*<<< orphan*/  reg_w_ixbuf (struct gspca_dev*,int,int const*,int) ; 
 struct additional_sensor_data* sensor_data ; 
 int /*<<< orphan*/  setfreq (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int** tas5130a_sensor_init ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	const struct additional_sensor_data *sensor;
	int i, mode;
	u8 t2[] = { 0x07, 0x00, 0x0d, 0x60, 0x0e, 0x80 };
	static const u8 t3[] =
		{ 0x07, 0x00, 0x88, 0x02, 0x06, 0x00, 0xe7, 0x01 };

	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	switch (mode) {
	case 0:		/* 640x480 (0x00) */
		break;
	case 1:		/* 352x288 */
		t2[1] = 0x40;
		break;
	case 2:		/* 320x240 */
		t2[1] = 0x10;
		break;
	case 3:		/* 176x144 */
		t2[1] = 0x50;
		break;
	default:
/*	case 4:		 * 160x120 */
		t2[1] = 0x20;
		break;
	}

	switch (sd->sensor) {
	case SENSOR_OM6802:
		om6802_sensor_init(gspca_dev);
		break;
	case SENSOR_TAS5130A:
		i = 0;
		for (;;) {
			reg_w_buf(gspca_dev, tas5130a_sensor_init[i],
					 sizeof tas5130a_sensor_init[0]);
			if (i >= ARRAY_SIZE(tas5130a_sensor_init) - 1)
				break;
			i++;
		}
		reg_w(gspca_dev, 0x3c80);
		/* just in case and to keep sync with logs (for mine) */
		reg_w_buf(gspca_dev, tas5130a_sensor_init[i],
				 sizeof tas5130a_sensor_init[0]);
		reg_w(gspca_dev, 0x3c80);
		break;
	}
	sensor = &sensor_data[sd->sensor];
	setfreq(gspca_dev, v4l2_ctrl_g_ctrl(sd->freq));
	reg_r(gspca_dev, 0x0012);
	reg_w_buf(gspca_dev, t2, sizeof t2);
	reg_w_ixbuf(gspca_dev, 0xb3, t3, sizeof t3);
	reg_w(gspca_dev, 0x0013);
	msleep(15);
	reg_w_buf(gspca_dev, sensor->stream, sizeof sensor->stream);
	reg_w_buf(gspca_dev, sensor->stream, sizeof sensor->stream);

	if (sd->sensor == SENSOR_OM6802)
		poll_sensor(gspca_dev);

	return 0;
}