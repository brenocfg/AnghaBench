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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_algo_dp_aux_address (struct i2c_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_algo_dp_aux_stop (struct i2c_adapter*,int) ; 

__attribute__((used)) static void
i2c_dp_aux_reset_bus(struct i2c_adapter *adapter)
{
	(void) i2c_algo_dp_aux_address(adapter, 0, false);
	(void) i2c_algo_dp_aux_stop(adapter, false);
}