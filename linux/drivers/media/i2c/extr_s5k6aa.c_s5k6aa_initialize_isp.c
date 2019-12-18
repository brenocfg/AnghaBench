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
struct s5k6aa {int apply_crop; int apply_cfg; int /*<<< orphan*/  mipi_lanes; int /*<<< orphan*/  bus_type; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  s5k6aa_analog_config ; 
 int s5k6aa_configure_pixel_clocks (struct s5k6aa*) ; 
 int s5k6aa_configure_video_bus (struct s5k6aa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s5k6aa_set_ahb_address (struct i2c_client*) ; 
 int s5k6aa_write_array (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct s5k6aa* to_s5k6aa (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k6aa_initialize_isp(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct s5k6aa *s5k6aa = to_s5k6aa(sd);
	int ret;

	s5k6aa->apply_crop = 1;
	s5k6aa->apply_cfg = 1;
	msleep(100);

	ret = s5k6aa_set_ahb_address(client);
	if (ret)
		return ret;
	ret = s5k6aa_configure_video_bus(s5k6aa, s5k6aa->bus_type,
					 s5k6aa->mipi_lanes);
	if (ret)
		return ret;
	ret = s5k6aa_write_array(sd, s5k6aa_analog_config);
	if (ret)
		return ret;
	msleep(20);

	return s5k6aa_configure_pixel_clocks(s5k6aa);
}