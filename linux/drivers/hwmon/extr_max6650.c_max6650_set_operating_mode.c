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
typedef  int u8 ;
struct max6650_data {int config; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int MAX6650_CFG_MODE_MASK ; 
 int /*<<< orphan*/  MAX6650_REG_CONFIG ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max6650_set_operating_mode(struct max6650_data *data, u8 mode)
{
	int result;
	u8 config = data->config;

	if (mode == (config & MAX6650_CFG_MODE_MASK))
		return 0;

	config = (config & ~MAX6650_CFG_MODE_MASK) | mode;

	result = i2c_smbus_write_byte_data(data->client, MAX6650_REG_CONFIG,
					   config);
	if (result < 0)
		return result;

	data->config = config;

	return 0;
}