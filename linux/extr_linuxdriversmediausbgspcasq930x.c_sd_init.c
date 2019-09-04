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
struct sd {int* gpio; size_t sensor; } ;
struct gspca_dev {scalar_t__ usb_err; int* usb_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 size_t SENSOR_ICX098BQ ; 
 size_t SENSOR_MI0360 ; 
 int /*<<< orphan*/  SQ930_CTRL_GET_DEV_INFO ; 
 int /*<<< orphan*/  bridge_init (struct sd*) ; 
 int /*<<< orphan*/  cmos_probe (struct gspca_dev*) ; 
 int /*<<< orphan*/  global_init (struct sd*,int) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sensor_tb ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->gpio[0] = sd->gpio[1] = 0xff;	/* force gpio rewrite */

/*fixme: is this needed for icx098bp and mi0360?
	if (sd->sensor != SENSOR_LZ24BP)
		reg_w(gspca_dev, SQ930_CTRL_RESET, 0x0000);
 */

	reg_r(gspca_dev, SQ930_CTRL_GET_DEV_INFO, 8);
	if (gspca_dev->usb_err < 0)
		return gspca_dev->usb_err;

/* it returns:
 * 03 00 12 93 0b f6 c9 00	live! ultra
 * 03 00 07 93 0b f6 ca 00	live! ultra for notebook
 * 03 00 12 93 0b fe c8 00	Trust WB-3500T
 * 02 00 06 93 0b fe c8 00	Joy-IT 318S
 * 03 00 12 93 0b f6 cf 00	icam tracer - sensor icx098bq
 * 02 00 12 93 0b fe cf 00	ProQ Motion Webcam
 *
 * byte
 * 0: 02 = usb 1.0 (12Mbit) / 03 = usb2.0 (480Mbit)
 * 1: 00
 * 2: 06 / 07 / 12 = mode webcam? firmware??
 * 3: 93 chip = 930b (930b or 930c)
 * 4: 0b
 * 5: f6 = cdd (icx098bq, lz24bp) / fe or de = cmos (i2c) (other sensors)
 * 6: c8 / c9 / ca / cf = mode webcam?, sensor? webcam?
 * 7: 00
 */
	gspca_dbg(gspca_dev, D_PROBE, "info: %*ph\n", 8, gspca_dev->usb_buf);

	bridge_init(sd);

	if (sd->sensor == SENSOR_MI0360) {

		/* no sensor probe for icam tracer */
		if (gspca_dev->usb_buf[5] == 0xf6)	/* if ccd */
			sd->sensor = SENSOR_ICX098BQ;
		else
			cmos_probe(gspca_dev);
	}
	if (gspca_dev->usb_err >= 0) {
		gspca_dbg(gspca_dev, D_PROBE, "Sensor %s\n",
			  sensor_tb[sd->sensor].name);
		global_init(sd, 1);
	}
	return gspca_dev->usb_err;
}