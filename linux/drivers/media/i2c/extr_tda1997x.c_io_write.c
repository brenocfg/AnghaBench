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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_state {int /*<<< orphan*/  page_lock; int /*<<< orphan*/  client; } ;
typedef  int s32 ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tda1997x_setpage (struct v4l2_subdev*,int) ; 
 struct tda1997x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_write(struct v4l2_subdev *sd, u16 reg, u8 val)
{
	struct tda1997x_state *state = to_state(sd);
	s32 ret = 0;

	mutex_lock(&state->page_lock);
	if (tda1997x_setpage(sd, reg >> 8)) {
		ret = -1;
		goto out;
	}

	ret = i2c_smbus_write_byte_data(state->client, reg & 0xff, val);
	if (ret < 0) {
		v4l_err(state->client, "write reg error:reg=%2x,val=%2x\n",
			reg&0xff, val);
		ret = -1;
		goto out;
	}

out:
	mutex_unlock(&state->page_lock);
	return ret;
}