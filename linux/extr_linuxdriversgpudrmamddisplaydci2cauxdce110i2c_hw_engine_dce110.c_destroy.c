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
struct i2c_hw_engine_dce110 {int /*<<< orphan*/  base; } ;
struct i2c_engine {int dummy; } ;

/* Variables and functions */
 struct i2c_hw_engine_dce110* FROM_I2C_ENGINE (struct i2c_engine*) ; 
 int /*<<< orphan*/  dal_i2c_hw_engine_destruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i2c_hw_engine_dce110*) ; 

__attribute__((used)) static void destroy(
	struct i2c_engine **i2c_engine)
{
	struct i2c_hw_engine_dce110 *engine_dce110 =
			FROM_I2C_ENGINE(*i2c_engine);

	dal_i2c_hw_engine_destruct(&engine_dce110->base);

	kfree(engine_dce110);

	*i2c_engine = NULL;
}