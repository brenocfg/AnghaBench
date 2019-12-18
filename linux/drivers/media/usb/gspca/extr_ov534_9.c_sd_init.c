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
typedef  int u16 ;
struct sd {int /*<<< orphan*/  sensor; } ;
struct TYPE_2__ {int bulk; int bulk_size; int bulk_nurbs; void* nmodes; void* cam_mode; } ;
struct gspca_dev {int usb_err; TYPE_1__ cam; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  D_PROBE ; 
 int EINVAL ; 
 int OV534_REG_ADDRESS ; 
 int /*<<< orphan*/  SENSOR_OV361x ; 
 int /*<<< orphan*/  SENSOR_OV562x ; 
 int /*<<< orphan*/  SENSOR_OV965x ; 
 int /*<<< orphan*/  SENSOR_OV971x ; 
 void* bridge_init ; 
 void* bridge_init_2 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 void* ov361x_mode ; 
 void* ov562x_init ; 
 void* ov562x_init_2 ; 
 void* ov562x_mode ; 
 void* ov965x_init ; 
 void* ov965x_init_2 ; 
 void* ov965x_mode ; 
 void* ov971x_init ; 
 void* ov971x_mode ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w_array (struct gspca_dev*,void*,void*) ; 
 int sccb_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_w_array (struct gspca_dev*,void*,void*) ; 
 int /*<<< orphan*/  sccb_write (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  set_led (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 char* video_device_node_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u16 sensor_id;

	/* reset bridge */
	reg_w(gspca_dev, 0xe7, 0x3a);
	reg_w(gspca_dev, 0xe0, 0x08);
	msleep(100);

	/* initialize the sensor address */
	reg_w(gspca_dev, OV534_REG_ADDRESS, 0x60);

	/* reset sensor */
	sccb_write(gspca_dev, 0x12, 0x80);
	msleep(10);

	/* probe the sensor */
	sccb_read(gspca_dev, 0x0a);
	sensor_id = sccb_read(gspca_dev, 0x0a) << 8;
	sccb_read(gspca_dev, 0x0b);
	sensor_id |= sccb_read(gspca_dev, 0x0b);
	gspca_dbg(gspca_dev, D_PROBE, "Sensor ID: %04x\n", sensor_id);

	/* initialize */
	if ((sensor_id & 0xfff0) == 0x9650) {
		sd->sensor = SENSOR_OV965x;

		gspca_dev->cam.cam_mode = ov965x_mode;
		gspca_dev->cam.nmodes = ARRAY_SIZE(ov965x_mode);

		reg_w_array(gspca_dev, bridge_init,
				ARRAY_SIZE(bridge_init));
		sccb_w_array(gspca_dev, ov965x_init,
				ARRAY_SIZE(ov965x_init));
		reg_w_array(gspca_dev, bridge_init_2,
				ARRAY_SIZE(bridge_init_2));
		sccb_w_array(gspca_dev, ov965x_init_2,
				ARRAY_SIZE(ov965x_init_2));
		reg_w(gspca_dev, 0xe0, 0x00);
		reg_w(gspca_dev, 0xe0, 0x01);
		set_led(gspca_dev, 0);
		reg_w(gspca_dev, 0xe0, 0x00);
	} else if ((sensor_id & 0xfff0) == 0x9710) {
		const char *p;
		int l;

		sd->sensor = SENSOR_OV971x;

		gspca_dev->cam.cam_mode = ov971x_mode;
		gspca_dev->cam.nmodes = ARRAY_SIZE(ov971x_mode);

		gspca_dev->cam.bulk = 1;
		gspca_dev->cam.bulk_size = 16384;
		gspca_dev->cam.bulk_nurbs = 2;

		sccb_w_array(gspca_dev, ov971x_init,
				ARRAY_SIZE(ov971x_init));

		/* set video format on bridge processor */
		/* access bridge processor's video format registers at: 0x00 */
		reg_w(gspca_dev, 0x1c, 0x00);
		/*set register: 0x00 is 'RAW8', 0x40 is 'YUV422' (YUYV?)*/
		reg_w(gspca_dev, 0x1d, 0x00);

		/* Will W. specific stuff
		 * set VSYNC to
		 *	output (0x1f) if first webcam
		 *	input (0x17) if 2nd or 3rd webcam */
		p = video_device_node_name(&gspca_dev->vdev);
		l = strlen(p) - 1;
		if (p[l] == '0')
			reg_w(gspca_dev, 0x56, 0x1f);
		else
			reg_w(gspca_dev, 0x56, 0x17);
	} else if ((sensor_id & 0xfff0) == 0x5620) {
		sd->sensor = SENSOR_OV562x;
		gspca_dev->cam.cam_mode = ov562x_mode;
		gspca_dev->cam.nmodes = ARRAY_SIZE(ov562x_mode);

		reg_w_array(gspca_dev, ov562x_init,
				ARRAY_SIZE(ov562x_init));
		sccb_w_array(gspca_dev, ov562x_init_2,
				ARRAY_SIZE(ov562x_init_2));
		reg_w(gspca_dev, 0xe0, 0x00);
	} else if ((sensor_id & 0xfff0) == 0x3610) {
		sd->sensor = SENSOR_OV361x;
		gspca_dev->cam.cam_mode = ov361x_mode;
		gspca_dev->cam.nmodes = ARRAY_SIZE(ov361x_mode);
		reg_w(gspca_dev, 0xe7, 0x3a);
		reg_w(gspca_dev, 0xf1, 0x60);
		sccb_write(gspca_dev, 0x12, 0x80);
	} else {
		pr_err("Unknown sensor %04x", sensor_id);
		return -EINVAL;
	}

	return gspca_dev->usb_err;
}