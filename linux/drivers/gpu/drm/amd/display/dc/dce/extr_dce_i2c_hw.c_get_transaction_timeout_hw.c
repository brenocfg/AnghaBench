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
typedef  int uint32_t ;
struct dce_i2c_hw {int buffer_used_bytes; int transaction_count; } ;

/* Variables and functions */
 int TRANSACTION_TIMEOUT_IN_I2C_CLOCKS ; 
 int get_speed (struct dce_i2c_hw const*) ; 

__attribute__((used)) static uint32_t get_transaction_timeout_hw(
	const struct dce_i2c_hw *dce_i2c_hw,
	uint32_t length)
{

	uint32_t speed = get_speed(dce_i2c_hw);



	uint32_t period_timeout;
	uint32_t num_of_clock_stretches;

	if (!speed)
		return 0;

	period_timeout = (1000 * TRANSACTION_TIMEOUT_IN_I2C_CLOCKS) / speed;

	num_of_clock_stretches = 1 + (length << 3) + 1;
	num_of_clock_stretches +=
		(dce_i2c_hw->buffer_used_bytes << 3) +
		(dce_i2c_hw->transaction_count << 1);

	return period_timeout * num_of_clock_stretches;
}