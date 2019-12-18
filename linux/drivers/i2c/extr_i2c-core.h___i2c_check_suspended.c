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
struct i2c_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  locked_flags; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int /*<<< orphan*/  I2C_ALF_IS_SUSPENDED ; 
 int /*<<< orphan*/  I2C_ALF_SUSPEND_REPORTED ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int __i2c_check_suspended(struct i2c_adapter *adap)
{
	if (test_bit(I2C_ALF_IS_SUSPENDED, &adap->locked_flags)) {
		if (!test_and_set_bit(I2C_ALF_SUSPEND_REPORTED, &adap->locked_flags))
			dev_WARN(&adap->dev, "Transfer while suspended\n");
		return -ESHUTDOWN;
	}

	return 0;
}