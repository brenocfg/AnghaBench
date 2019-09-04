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
struct i2c_regval {scalar_t__ addr; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 scalar_t__ REG_TERM ; 
 int cam_i2c_write (struct v4l2_subdev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sr030pc30_bulk_write_reg(struct v4l2_subdev *sd,
				const struct i2c_regval *msg)
{
	while (msg->addr != REG_TERM) {
		int ret = cam_i2c_write(sd, msg->addr, msg->val);
		if (ret)
			return ret;
		msg++;
	}
	return 0;
}