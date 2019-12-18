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
struct i2c_client {int dummy; } ;

/* Variables and functions */
#define  UDA1342_IN1 129 
#define  UDA1342_IN2 128 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  write_reg (struct i2c_client*,int,int) ; 

__attribute__((used)) static int uda1342_s_routing(struct v4l2_subdev *sd,
		u32 input, u32 output, u32 config)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	switch (input) {
	case UDA1342_IN1:
		write_reg(client, 0x00, 0x1241); /* select input 1 */
		break;
	case UDA1342_IN2:
		write_reg(client, 0x00, 0x1441); /* select input 2 */
		break;
	default:
		v4l2_err(sd, "input %d not supported\n", input);
		break;
	}
	return 0;
}