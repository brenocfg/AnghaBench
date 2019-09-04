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
typedef  int v4l2_std_id ;
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct ak881x {int lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK881X_VIDEO_PROCESS1 ; 
 int EINVAL ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_NTSC_443 ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_M ; 
 int /*<<< orphan*/  reg_set (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 
 struct ak881x* to_ak881x (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ak881x_s_std_output(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ak881x *ak881x = to_ak881x(client);
	u8 vp1;

	if (std == V4L2_STD_NTSC_443) {
		vp1 = 3;
		ak881x->lines = 480;
	} else if (std == V4L2_STD_PAL_M) {
		vp1 = 5;
		ak881x->lines = 480;
	} else if (std == V4L2_STD_PAL_60) {
		vp1 = 7;
		ak881x->lines = 480;
	} else if (std & V4L2_STD_NTSC) {
		vp1 = 0;
		ak881x->lines = 480;
	} else if (std & V4L2_STD_PAL) {
		vp1 = 0xf;
		ak881x->lines = 576;
	} else {
		/* No SECAM or PAL_N/Nc supported */
		return -EINVAL;
	}

	reg_set(client, AK881X_VIDEO_PROCESS1, vp1, 0xf);

	return 0;
}