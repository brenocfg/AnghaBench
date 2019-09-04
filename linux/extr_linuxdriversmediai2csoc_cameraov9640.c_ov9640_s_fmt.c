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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; int /*<<< orphan*/  width; } ;
struct ov9640_reg_alt {int /*<<< orphan*/  member_0; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ov9640_alter_regs (int /*<<< orphan*/ ,struct ov9640_reg_alt*) ; 
 int ov9640_prog_dflt (struct i2c_client*) ; 
 int /*<<< orphan*/  ov9640_reset (struct i2c_client*) ; 
 int ov9640_write_regs (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ov9640_reg_alt*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov9640_s_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov9640_reg_alt alts = {0};
	int ret;

	ov9640_alter_regs(mf->code, &alts);

	ov9640_reset(client);

	ret = ov9640_prog_dflt(client);
	if (ret)
		return ret;

	return ov9640_write_regs(client, mf->width, mf->code, &alts);
}