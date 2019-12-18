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
struct tcs3414_data {int control; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCS3414_CONTROL ; 
 int TCS3414_CONTROL_ADC_EN ; 
 int TCS3414_CONTROL_POWER ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcs3414_powerdown(struct tcs3414_data *data)
{
	return i2c_smbus_write_byte_data(data->client, TCS3414_CONTROL,
		data->control & ~(TCS3414_CONTROL_POWER |
		TCS3414_CONTROL_ADC_EN));
}