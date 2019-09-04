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
struct tw2804 {int norm; int /*<<< orphan*/  channel; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 struct tw2804* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  write_regs (struct i2c_client*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw2804_s_std(struct v4l2_subdev *sd, v4l2_std_id norm)
{
	struct tw2804 *dec = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	bool is_60hz = norm & V4L2_STD_525_60;
	u8 regs[] = {
		0x01, is_60hz ? 0xc4 : 0x84,
		0x09, is_60hz ? 0x07 : 0x04,
		0x0a, is_60hz ? 0xf0 : 0x20,
		0x0b, is_60hz ? 0x07 : 0x04,
		0x0c, is_60hz ? 0xf0 : 0x20,
		0x0d, is_60hz ? 0x40 : 0x4a,
		0x16, is_60hz ? 0x00 : 0x40,
		0x17, is_60hz ? 0x00 : 0x40,
		0x20, is_60hz ? 0x07 : 0x0f,
		0x21, is_60hz ? 0x07 : 0x0f,
		0xff, 0xff,
	};

	write_regs(client, regs, dec->channel);
	dec->norm = norm;
	return 0;
}