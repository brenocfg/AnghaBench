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
typedef  unsigned int u32 ;
struct imx258_reg {int /*<<< orphan*/  address; int /*<<< orphan*/  val; } ;
struct imx258 {int /*<<< orphan*/  sd; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int imx258_write_reg (struct imx258*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx258_write_regs(struct imx258 *imx258,
			     const struct imx258_reg *regs, u32 len)
{
	struct i2c_client *client = v4l2_get_subdevdata(&imx258->sd);
	unsigned int i;
	int ret;

	for (i = 0; i < len; i++) {
		ret = imx258_write_reg(imx258, regs[i].address, 1,
					regs[i].val);
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