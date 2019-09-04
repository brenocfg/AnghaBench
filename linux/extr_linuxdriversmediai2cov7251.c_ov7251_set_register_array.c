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
struct ov7251 {int dummy; } ;

/* Variables and functions */
 int ov7251_write_reg (struct ov7251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov7251_set_register_array(struct ov7251 *ov7251,
				     const struct reg_value *settings,
				     unsigned int num_settings)
{
	unsigned int i;
	int ret;

	for (i = 0; i < num_settings; ++i, ++settings) {
		ret = ov7251_write_reg(ov7251, settings->reg, settings->val);
		if (ret < 0)
			return ret;
	}

	return 0;
}