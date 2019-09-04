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
struct ti_lmu {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct ti_lmu* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_lmu_disable_hw (struct ti_lmu*) ; 

__attribute__((used)) static int ti_lmu_remove(struct i2c_client *cl)
{
	struct ti_lmu *lmu = i2c_get_clientdata(cl);

	ti_lmu_disable_hw(lmu);
	mfd_remove_devices(lmu->dev);
	return 0;
}