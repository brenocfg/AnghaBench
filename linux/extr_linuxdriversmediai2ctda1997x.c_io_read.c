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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_state {int /*<<< orphan*/  page_lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tda1997x_setpage (struct v4l2_subdev*,int) ; 
 struct tda1997x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline int io_read(struct v4l2_subdev *sd, u16 reg)
{
	struct tda1997x_state *state = to_state(sd);
	int val;

	mutex_lock(&state->page_lock);
	if (tda1997x_setpage(sd, reg >> 8)) {
		val = -1;
		goto out;
	}

	val = i2c_smbus_read_byte_data(state->client, reg&0xff);
	if (val < 0) {
		v4l_err(state->client, "read reg error: reg=%2x\n", reg & 0xff);
		val = -1;
		goto out;
	}

out:
	mutex_unlock(&state->page_lock);
	return val;
}