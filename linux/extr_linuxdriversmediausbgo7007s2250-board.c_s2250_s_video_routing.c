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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct s2250 {scalar_t__ std; int input; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_STD_NTSC ; 
 struct s2250* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  write_reg_fp (struct i2c_client*,int,int) ; 

__attribute__((used)) static int s2250_s_video_routing(struct v4l2_subdev *sd, u32 input, u32 output,
				 u32 config)
{
	struct s2250 *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int vidsys;

	vidsys = (state->std == V4L2_STD_NTSC) ? 0x01 : 0x00;
	if (input == 0) {
		/* composite */
		write_reg_fp(client, 0x20, 0x020 | vidsys);
		write_reg_fp(client, 0x21, 0x662);
		write_reg_fp(client, 0x140, 0x060);
	} else if (input == 1) {
		/* S-Video */
		write_reg_fp(client, 0x20, 0x040 | vidsys);
		write_reg_fp(client, 0x21, 0x666);
		write_reg_fp(client, 0x140, 0x060);
	} else {
		return -EINVAL;
	}
	state->input = input;
	return 0;
}