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
 int US5182D_AGAIN_MASK ; 
 int /*<<< orphan*/  US5182D_REG_CFG1 ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int us5182d_update_dark_th (struct us5182d_data*,int) ; 

__attribute__((used)) static int us5182d_apply_scale(struct us5182d_data *data, int index)
{
	int ret;

	ret = i2c_smbus_read_byte_data(data->client, US5182D_REG_CFG1);
	if (ret < 0)
		return ret;

	ret = ret & (~US5182D_AGAIN_MASK);
	ret |= index;

	ret = i2c_smbus_write_byte_data(data->client, US5182D_REG_CFG1, ret);
	if (ret < 0)
		return ret;

	return us5182d_update_dark_th(data, index);
}