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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct m52790_state {int input; int output; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 
 struct m52790_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int m52790_write(struct v4l2_subdev *sd)
{
	struct m52790_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	u8 sw1 = (state->input | state->output) & 0xff;
	u8 sw2 = (state->input | state->output) >> 8;

	return i2c_smbus_write_byte_data(client, sw1, sw2);
}