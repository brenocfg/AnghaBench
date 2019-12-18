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
typedef  scalar_t__ uint32_t ;
struct dce_i2c_hw {int dummy; } ;
typedef  enum i2c_channel_operation_result { ____Placeholder_i2c_channel_operation_result } i2c_channel_operation_result ;

/* Variables and functions */
 int I2C_CHANNEL_OPERATION_SUCCEEDED ; 
 int get_channel_status (struct dce_i2c_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

enum i2c_channel_operation_result dce_i2c_hw_engine_wait_on_operation_result(
	struct dce_i2c_hw *dce_i2c_hw,
	uint32_t timeout,
	enum i2c_channel_operation_result expected_result)
{
	enum i2c_channel_operation_result result;
	uint32_t i = 0;

	if (!timeout)
		return I2C_CHANNEL_OPERATION_SUCCEEDED;

	do {

		result = get_channel_status(
				dce_i2c_hw, NULL);

		if (result != expected_result)
			break;

		udelay(1);

		++i;
	} while (i < timeout);
	return result;
}