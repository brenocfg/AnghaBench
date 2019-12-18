#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct sd {int sensor; int reg11; } ;
struct TYPE_5__ {int width; } ;
struct gspca_dev {TYPE_3__* exposure; int /*<<< orphan*/  usb_err; TYPE_2__* autogain; TYPE_1__ pixfmt; } ;
typedef  int __u8 ;
struct TYPE_8__ {int sensor_addr; } ;
struct TYPE_7__ {int val; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
#define  SENSOR_HV7131D 134 
#define  SENSOR_OV6650 133 
#define  SENSOR_OV7630 132 
#define  SENSOR_PAS106 131 
#define  SENSOR_PAS202 130 
#define  SENSOR_TAS5110C 129 
#define  SENSOR_TAS5110D 128 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int const*) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 
 TYPE_4__* sensor_data ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->sensor) {
	case SENSOR_HV7131D: {
		/* Note the datasheet wrongly says line mode exposure uses reg
		   0x26 and 0x27, testing has shown 0x25 + 0x26 */
		__u8 i2c[] = {0xc0, 0x11, 0x25, 0x00, 0x00, 0x00, 0x00, 0x17};
		u16 reg = gspca_dev->exposure->val;

		i2c[3] = reg >> 8;
		i2c[4] = reg & 0xff;
		i2c_w(gspca_dev, i2c);
		break;
	}
	case SENSOR_TAS5110C:
	case SENSOR_TAS5110D: {
		/* register 19's high nibble contains the sn9c10x clock divider
		   The high nibble configures the no fps according to the
		   formula: 60 / high_nibble. With a maximum of 30 fps */
		u8 reg = gspca_dev->exposure->val;

		reg = (reg << 4) | 0x0b;
		reg_w(gspca_dev, 0x19, &reg, 1);
		break;
	}
	case SENSOR_OV6650:
	case SENSOR_OV7630: {
		/* The ov6650 / ov7630 have 2 registers which both influence
		   exposure, register 11, whose low nibble sets the nr off fps
		   according to: fps = 30 / (low_nibble + 1)

		   The fps configures the maximum exposure setting, but it is
		   possible to use less exposure then what the fps maximum
		   allows by setting register 10. register 10 configures the
		   actual exposure as quotient of the full exposure, with 0
		   being no exposure at all (not very useful) and reg10_max
		   being max exposure possible at that framerate.

		   The code maps our 0 - 510 ms exposure ctrl to these 2
		   registers, trying to keep fps as high as possible.
		*/
		__u8 i2c[] = {0xb0, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10};
		int reg10, reg11, reg10_max;

		/* ov6645 datasheet says reg10_max is 9a, but that uses
		   tline * 2 * reg10 as formula for calculating texpo, the
		   ov6650 probably uses the same formula as the 7730 which uses
		   tline * 4 * reg10, which explains why the reg10max we've
		   found experimentally for the ov6650 is exactly half that of
		   the ov6645. The ov7630 datasheet says the max is 0x41. */
		if (sd->sensor == SENSOR_OV6650) {
			reg10_max = 0x4d;
			i2c[4] = 0xc0; /* OV6650 needs non default vsync pol */
		} else
			reg10_max = 0x41;

		reg11 = (15 * gspca_dev->exposure->val + 999) / 1000;
		if (reg11 < 1)
			reg11 = 1;
		else if (reg11 > 16)
			reg11 = 16;

		/* In 640x480, if the reg11 has less than 4, the image is
		   unstable (the bridge goes into a higher compression mode
		   which we have not reverse engineered yet). */
		if (gspca_dev->pixfmt.width == 640 && reg11 < 4)
			reg11 = 4;

		/* frame exposure time in ms = 1000 * reg11 / 30    ->
		reg10 = (gspca_dev->exposure->val / 2) * reg10_max
				/ (1000 * reg11 / 30) */
		reg10 = (gspca_dev->exposure->val * 15 * reg10_max)
				/ (1000 * reg11);

		/* Don't allow this to get below 10 when using autogain, the
		   steps become very large (relatively) when below 10 causing
		   the image to oscillate from much too dark, to much too bright
		   and back again. */
		if (gspca_dev->autogain->val && reg10 < 10)
			reg10 = 10;
		else if (reg10 > reg10_max)
			reg10 = reg10_max;

		/* Write reg 10 and reg11 low nibble */
		i2c[1] = sensor_data[sd->sensor].sensor_addr;
		i2c[3] = reg10;
		i2c[4] |= reg11 - 1;

		/* If register 11 didn't change, don't change it */
		if (sd->reg11 == reg11)
			i2c[0] = 0xa0;

		i2c_w(gspca_dev, i2c);
		if (gspca_dev->usb_err == 0)
			sd->reg11 = reg11;
		break;
	}
	case SENSOR_PAS202: {
		__u8 i2cpframerate[] =
			{0xb0, 0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x16};
		__u8 i2cpexpo[] =
			{0xa0, 0x40, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x16};
		const __u8 i2cpdoit[] =
			{0xa0, 0x40, 0x11, 0x01, 0x00, 0x00, 0x00, 0x16};
		int framerate_ctrl;

		/* The exposure knee for the autogain algorithm is 200
		   (100 ms / 10 fps on other sensors), for values below this
		   use the control for setting the partial frame expose time,
		   above that use variable framerate. This way we run at max
		   framerate (640x480@7.5 fps, 320x240@10fps) until the knee
		   is reached. Using the variable framerate control above 200
		   is better then playing around with both clockdiv + partial
		   frame exposure times (like we are doing with the ov chips),
		   as that sometimes leads to jumps in the exposure control,
		   which are bad for auto exposure. */
		if (gspca_dev->exposure->val < 200) {
			i2cpexpo[3] = 255 - (gspca_dev->exposure->val * 255)
						/ 200;
			framerate_ctrl = 500;
		} else {
			/* The PAS202's exposure control goes from 0 - 4095,
			   but anything below 500 causes vsync issues, so scale
			   our 200-1023 to 500-4095 */
			framerate_ctrl = (gspca_dev->exposure->val - 200)
							* 1000 / 229 +  500;
		}

		i2cpframerate[3] = framerate_ctrl >> 6;
		i2cpframerate[4] = framerate_ctrl & 0x3f;
		i2c_w(gspca_dev, i2cpframerate);
		i2c_w(gspca_dev, i2cpexpo);
		i2c_w(gspca_dev, i2cpdoit);
		break;
	}
	case SENSOR_PAS106: {
		__u8 i2cpframerate[] =
			{0xb1, 0x40, 0x03, 0x00, 0x00, 0x00, 0x00, 0x14};
		__u8 i2cpexpo[] =
			{0xa1, 0x40, 0x05, 0x00, 0x00, 0x00, 0x00, 0x14};
		const __u8 i2cpdoit[] =
			{0xa1, 0x40, 0x13, 0x01, 0x00, 0x00, 0x00, 0x14};
		int framerate_ctrl;

		/* For values below 150 use partial frame exposure, above
		   that use framerate ctrl */
		if (gspca_dev->exposure->val < 150) {
			i2cpexpo[3] = 150 - gspca_dev->exposure->val;
			framerate_ctrl = 300;
		} else {
			/* The PAS106's exposure control goes from 0 - 4095,
			   but anything below 300 causes vsync issues, so scale
			   our 150-1023 to 300-4095 */
			framerate_ctrl = (gspca_dev->exposure->val - 150)
						* 1000 / 230 + 300;
		}

		i2cpframerate[3] = framerate_ctrl >> 4;
		i2cpframerate[4] = framerate_ctrl & 0x0f;
		i2c_w(gspca_dev, i2cpframerate);
		i2c_w(gspca_dev, i2cpexpo);
		i2c_w(gspca_dev, i2cpdoit);
		break;
	}
	default:
		break;
	}
}