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
struct i2c_client {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX90614_CONFIG ; 
 int MLX90614_CONFIG_DUAL_MASK ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx90614_probe_num_ir_sensors(struct i2c_client *client)
{
	s32 ret;

	ret = i2c_smbus_read_word_data(client, MLX90614_CONFIG);

	if (ret < 0)
		return ret;

	return (ret & MLX90614_CONFIG_DUAL_MASK) ? 1 : 0;
}