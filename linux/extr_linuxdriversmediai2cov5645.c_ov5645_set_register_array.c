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
struct reg_value {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
struct ov5645 {int dummy; } ;

/* Variables and functions */
 int ov5645_write_reg (struct ov5645*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5645_set_register_array(struct ov5645 *ov5645,
				     const struct reg_value *settings,
				     unsigned int num_settings)
{
	unsigned int i;
	int ret;

	for (i = 0; i < num_settings; ++i, ++settings) {
		ret = ov5645_write_reg(ov5645, settings->reg, settings->val);
		if (ret < 0)
			return ret;
	}

	return 0;
}