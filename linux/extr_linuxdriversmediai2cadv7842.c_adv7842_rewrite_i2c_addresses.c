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
struct v4l2_subdev {int dummy; } ;
struct adv7842_platform_data {int i2c_sdp; int i2c_sdp_io; int i2c_avlink; int i2c_cec; int i2c_infoframe; int i2c_afe; int i2c_repeater; int i2c_edid; int i2c_hdmi; int i2c_cp; int i2c_vdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int,int) ; 

__attribute__((used)) static void adv7842_rewrite_i2c_addresses(struct v4l2_subdev *sd,
		struct adv7842_platform_data *pdata)
{
	io_write(sd, 0xf1, pdata->i2c_sdp << 1);
	io_write(sd, 0xf2, pdata->i2c_sdp_io << 1);
	io_write(sd, 0xf3, pdata->i2c_avlink << 1);
	io_write(sd, 0xf4, pdata->i2c_cec << 1);
	io_write(sd, 0xf5, pdata->i2c_infoframe << 1);

	io_write(sd, 0xf8, pdata->i2c_afe << 1);
	io_write(sd, 0xf9, pdata->i2c_repeater << 1);
	io_write(sd, 0xfa, pdata->i2c_edid << 1);
	io_write(sd, 0xfb, pdata->i2c_hdmi << 1);

	io_write(sd, 0xfd, pdata->i2c_cp << 1);
	io_write(sd, 0xfe, pdata->i2c_vdp << 1);
}