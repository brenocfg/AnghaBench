#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* max8998_dump ; 
 int /*<<< orphan*/  max8998_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int max8998_restore(struct device *dev)
{
	struct i2c_client *i2c = to_i2c_client(dev);
	int i;

	for (i = 0; i < ARRAY_SIZE(max8998_dump); i++)
		max8998_write_reg(i2c, max8998_dump[i].addr,
				max8998_dump[i].val);

	return 0;
}