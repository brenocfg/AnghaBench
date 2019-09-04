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
struct us5182d_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int US5182D_CFG0_ONESHOT_EN ; 
 int /*<<< orphan*/  US5182D_REG_CFG0 ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int us5182d_oneshot_en(struct us5182d_data *data)
{
	int ret;

	ret = i2c_smbus_read_byte_data(data->client, US5182D_REG_CFG0);
	if (ret < 0)
		return ret;

	/*
	 * In oneshot mode the chip will power itself down after taking the
	 * required measurement.
	 */
	ret = ret | US5182D_CFG0_ONESHOT_EN;

	return i2c_smbus_write_byte_data(data->client, US5182D_REG_CFG0, ret);
}