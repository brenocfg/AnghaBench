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
struct mxc4005_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC4005_REG_INT_CLR1 ; 
 int /*<<< orphan*/  MXC4005_REG_INT_CLR1_BIT_DRDYC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxc4005_clr_intr(struct mxc4005_data *data)
{
	int ret;

	/* clear interrupt */
	ret = regmap_write(data->regmap, MXC4005_REG_INT_CLR1,
			   MXC4005_REG_INT_CLR1_BIT_DRDYC);
	if (ret < 0) {
		dev_err(data->dev, "failed to write to reg_int_clr1\n");
		return ret;
	}

	return 0;
}