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
struct ov5670_reg {int /*<<< orphan*/  address; int /*<<< orphan*/  val; } ;
struct ov5670 {int /*<<< orphan*/  sd; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int ov5670_write_reg (struct ov5670*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov5670_write_regs(struct ov5670 *ov5670,
			     const struct ov5670_reg *regs, unsigned int len)
{
	struct i2c_client *client = v4l2_get_subdevdata(&ov5670->sd);
	unsigned int i;
	int ret;

	for (i = 0; i < len; i++) {
		ret = ov5670_write_reg(ov5670, regs[i].address, 1, regs[i].val);
		if (ret) {
			dev_err_ratelimited(
				&client->dev,
				"Failed to write reg 0x%4.4x. error = %d\n",
				regs[i].address, ret);

			return ret;
		}
	}

	return 0;
}