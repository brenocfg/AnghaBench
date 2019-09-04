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
struct ina209_data {int /*<<< orphan*/  calibration_orig; int /*<<< orphan*/  config_orig; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INA209_CALIBRATION ; 
 int /*<<< orphan*/  INA209_CONFIGURATION ; 
 int /*<<< orphan*/  i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ina209_restore_conf(struct i2c_client *client,
				struct ina209_data *data)
{
	/* Restore initial configuration */
	i2c_smbus_write_word_swapped(client, INA209_CONFIGURATION,
				     data->config_orig);
	i2c_smbus_write_word_swapped(client, INA209_CALIBRATION,
				     data->calibration_orig);
}