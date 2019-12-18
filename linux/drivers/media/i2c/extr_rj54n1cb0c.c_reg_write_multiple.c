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
struct rj54n1_reg_val {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_write_multiple(struct i2c_client *client,
			      const struct rj54n1_reg_val *rv, const int n)
{
	int i, ret;

	for (i = 0; i < n; i++) {
		ret = reg_write(client, rv->reg, rv->val);
		if (ret < 0)
			return ret;
		rv++;
	}

	return 0;
}