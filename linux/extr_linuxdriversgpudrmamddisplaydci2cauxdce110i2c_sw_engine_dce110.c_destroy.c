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
struct i2c_sw_engine_dce110 {int dummy; } ;
struct i2c_engine {int dummy; } ;

/* Variables and functions */
 struct i2c_sw_engine_dce110* FROM_I2C_ENGINE (struct i2c_engine*) ; 
 int /*<<< orphan*/  destruct (struct i2c_sw_engine_dce110*) ; 
 int /*<<< orphan*/  kfree (struct i2c_sw_engine_dce110*) ; 

__attribute__((used)) static void destroy(
	struct i2c_engine **engine)
{
	struct i2c_sw_engine_dce110 *sw_engine = FROM_I2C_ENGINE(*engine);

	destruct(sw_engine);

	kfree(sw_engine);

	*engine = NULL;
}