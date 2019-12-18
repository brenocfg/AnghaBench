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
struct max44009_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int MAX44009_CFG_TIM_MASK ; 
 int /*<<< orphan*/  MAX44009_REG_CFG ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* max44009_int_time_ns_array ; 

__attribute__((used)) static int max44009_read_int_time(struct max44009_data *data)
{

	int ret = i2c_smbus_read_byte_data(data->client, MAX44009_REG_CFG);

	if (ret < 0)
		return ret;

	return max44009_int_time_ns_array[ret & MAX44009_CFG_TIM_MASK];
}