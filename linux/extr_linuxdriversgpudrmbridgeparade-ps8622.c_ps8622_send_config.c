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
struct ps8622_bridge {int max_lane_count; int lane_count; TYPE_2__* bl; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct TYPE_3__ {int brightness; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int EIO ; 
 int ps8622_set (struct i2c_client*,int,int,int) ; 

__attribute__((used)) static int ps8622_send_config(struct ps8622_bridge *ps8622)
{
	struct i2c_client *cl = ps8622->client;
	int err = 0;

	/* HPD low */
	err = ps8622_set(cl, 0x02, 0xa1, 0x01);
	if (err)
		goto error;

	/* SW setting: [1:0] SW output 1.2V voltage is lower to 96% */
	err = ps8622_set(cl, 0x04, 0x14, 0x01);
	if (err)
		goto error;

	/* RCO SS setting: [5:4] = b01 0.5%, b10 1%, b11 1.5% */
	err = ps8622_set(cl, 0x04, 0xe3, 0x20);
	if (err)
		goto error;

	/* [7] RCO SS enable */
	err = ps8622_set(cl, 0x04, 0xe2, 0x80);
	if (err)
		goto error;

	/* RPHY Setting
	 * [3:2] CDR tune wait cycle before measure for fine tune
	 * b00: 1us b01: 0.5us b10:2us, b11: 4us
	 */
	err = ps8622_set(cl, 0x04, 0x8a, 0x0c);
	if (err)
		goto error;

	/* [3] RFD always on */
	err = ps8622_set(cl, 0x04, 0x89, 0x08);
	if (err)
		goto error;

	/* CTN lock in/out: 20000ppm/80000ppm. Lock out 2 times. */
	err = ps8622_set(cl, 0x04, 0x71, 0x2d);
	if (err)
		goto error;

	/* 2.7G CDR settings: NOF=40LSB for HBR CDR  setting */
	err = ps8622_set(cl, 0x04, 0x7d, 0x07);
	if (err)
		goto error;

	/* [1:0] Fmin=+4bands */
	err = ps8622_set(cl, 0x04, 0x7b, 0x00);
	if (err)
		goto error;

	/* [7:5] DCO_FTRNG=+-40% */
	err = ps8622_set(cl, 0x04, 0x7a, 0xfd);
	if (err)
		goto error;

	/* 1.62G CDR settings: [5:2]NOF=64LSB [1:0]DCO scale is 2/5 */
	err = ps8622_set(cl, 0x04, 0xc0, 0x12);
	if (err)
		goto error;

	/* Gitune=-37% */
	err = ps8622_set(cl, 0x04, 0xc1, 0x92);
	if (err)
		goto error;

	/* Fbstep=100% */
	err = ps8622_set(cl, 0x04, 0xc2, 0x1c);
	if (err)
		goto error;

	/* [7] LOS signal disable */
	err = ps8622_set(cl, 0x04, 0x32, 0x80);
	if (err)
		goto error;

	/* RPIO Setting: [7:4] LVDS driver bias current : 75% (250mV swing) */
	err = ps8622_set(cl, 0x04, 0x00, 0xb0);
	if (err)
		goto error;

	/* [7:6] Right-bar GPIO output strength is 8mA */
	err = ps8622_set(cl, 0x04, 0x15, 0x40);
	if (err)
		goto error;

	/* EQ Training State Machine Setting, RCO calibration start */
	err = ps8622_set(cl, 0x04, 0x54, 0x10);
	if (err)
		goto error;

	/* Logic, needs more than 10 I2C command */
	/* [4:0] MAX_LANE_COUNT set to max supported lanes */
	err = ps8622_set(cl, 0x01, 0x02, 0x80 | ps8622->max_lane_count);
	if (err)
		goto error;

	/* [4:0] LANE_COUNT_SET set to chosen lane count */
	err = ps8622_set(cl, 0x01, 0x21, 0x80 | ps8622->lane_count);
	if (err)
		goto error;

	err = ps8622_set(cl, 0x00, 0x52, 0x20);
	if (err)
		goto error;

	/* HPD CP toggle enable */
	err = ps8622_set(cl, 0x00, 0xf1, 0x03);
	if (err)
		goto error;

	err = ps8622_set(cl, 0x00, 0x62, 0x41);
	if (err)
		goto error;

	/* Counter number, add 1ms counter delay */
	err = ps8622_set(cl, 0x00, 0xf6, 0x01);
	if (err)
		goto error;

	/* [6]PWM function control by DPCD0040f[7], default is PWM block */
	err = ps8622_set(cl, 0x00, 0x77, 0x06);
	if (err)
		goto error;

	/* 04h Adjust VTotal toleranceto fix the 30Hz no display issue */
	err = ps8622_set(cl, 0x00, 0x4c, 0x04);
	if (err)
		goto error;

	/* DPCD00400='h00, Parade OUI ='h001cf8 */
	err = ps8622_set(cl, 0x01, 0xc0, 0x00);
	if (err)
		goto error;

	/* DPCD00401='h1c */
	err = ps8622_set(cl, 0x01, 0xc1, 0x1c);
	if (err)
		goto error;

	/* DPCD00402='hf8 */
	err = ps8622_set(cl, 0x01, 0xc2, 0xf8);
	if (err)
		goto error;

	/* DPCD403~408 = ASCII code, D2SLV5='h4432534c5635 */
	err = ps8622_set(cl, 0x01, 0xc3, 0x44);
	if (err)
		goto error;

	/* DPCD404 */
	err = ps8622_set(cl, 0x01, 0xc4, 0x32);
	if (err)
		goto error;

	/* DPCD405 */
	err = ps8622_set(cl, 0x01, 0xc5, 0x53);
	if (err)
		goto error;

	/* DPCD406 */
	err = ps8622_set(cl, 0x01, 0xc6, 0x4c);
	if (err)
		goto error;

	/* DPCD407 */
	err = ps8622_set(cl, 0x01, 0xc7, 0x56);
	if (err)
		goto error;

	/* DPCD408 */
	err = ps8622_set(cl, 0x01, 0xc8, 0x35);
	if (err)
		goto error;

	/* DPCD40A, Initial Code major revision '01' */
	err = ps8622_set(cl, 0x01, 0xca, 0x01);
	if (err)
		goto error;

	/* DPCD40B, Initial Code minor revision '05' */
	err = ps8622_set(cl, 0x01, 0xcb, 0x05);
	if (err)
		goto error;


	if (ps8622->bl) {
		/* DPCD720, internal PWM */
		err = ps8622_set(cl, 0x01, 0xa5, 0xa0);
		if (err)
			goto error;

		/* FFh for 100% brightness, 0h for 0% brightness */
		err = ps8622_set(cl, 0x01, 0xa7,
				ps8622->bl->props.brightness);
		if (err)
			goto error;
	} else {
		/* DPCD720, external PWM */
		err = ps8622_set(cl, 0x01, 0xa5, 0x80);
		if (err)
			goto error;
	}

	/* Set LVDS output as 6bit-VESA mapping, single LVDS channel */
	err = ps8622_set(cl, 0x01, 0xcc, 0x13);
	if (err)
		goto error;

	/* Enable SSC set by register */
	err = ps8622_set(cl, 0x02, 0xb1, 0x20);
	if (err)
		goto error;

	/* Set SSC enabled and +/-1% central spreading */
	err = ps8622_set(cl, 0x04, 0x10, 0x16);
	if (err)
		goto error;

	/* Logic end */
	/* MPU Clock source: LC => RCO */
	err = ps8622_set(cl, 0x04, 0x59, 0x60);
	if (err)
		goto error;

	/* LC -> RCO */
	err = ps8622_set(cl, 0x04, 0x54, 0x14);
	if (err)
		goto error;

	/* HPD high */
	err = ps8622_set(cl, 0x02, 0xa1, 0x91);

error:
	return err ? -EIO : 0;
}