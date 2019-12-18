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
typedef  int /*<<< orphan*/  u32 ;
struct mpu3050 {int /*<<< orphan*/  dev; } ;
struct i2c_mux_core {int dummy; } ;

/* Variables and functions */
 struct mpu3050* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpu3050_i2c_bypass_select(struct i2c_mux_core *mux, u32 chan_id)
{
	struct mpu3050 *mpu3050 = i2c_mux_priv(mux);

	/* Just power up the device, that is all that is needed */
	pm_runtime_get_sync(mpu3050->dev);
	return 0;
}