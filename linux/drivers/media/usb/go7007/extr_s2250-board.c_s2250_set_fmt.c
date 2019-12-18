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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int height; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct s2250 {int reg12b_val; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 struct s2250* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  write_reg_fp (struct i2c_client*,int,int) ; 

__attribute__((used)) static int s2250_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *fmt = &format->format;
	struct s2250 *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (format->pad)
		return -EINVAL;

	if (format->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;

	if (fmt->height < 640) {
		write_reg_fp(client, 0x12b, state->reg12b_val | 0x400);
		write_reg_fp(client, 0x140, 0x060);
	} else {
		write_reg_fp(client, 0x12b, state->reg12b_val & ~0x400);
		write_reg_fp(client, 0x140, 0x060);
	}
	return 0;
}