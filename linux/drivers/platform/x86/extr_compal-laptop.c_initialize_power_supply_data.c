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
struct compal_data {int /*<<< orphan*/  bat_serial_number; scalar_t__* bat_model_name; scalar_t__* bat_manufacturer_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAT_MANUFACTURER_NAME_ADDR ; 
 size_t BAT_MANUFACTURER_NAME_LEN ; 
 int /*<<< orphan*/  BAT_MODEL_NAME_ADDR ; 
 size_t BAT_MODEL_NAME_LEN ; 
 int /*<<< orphan*/  BAT_SERIAL_NUMBER_ADDR ; 
 scalar_t__ BAT_SERIAL_NUMBER_LEN ; 
 int /*<<< orphan*/  ec_read_sequence (int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  ec_read_u16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initialize_power_supply_data(struct compal_data *data)
{
	ec_read_sequence(BAT_MANUFACTURER_NAME_ADDR,
					data->bat_manufacturer_name,
					BAT_MANUFACTURER_NAME_LEN);
	data->bat_manufacturer_name[BAT_MANUFACTURER_NAME_LEN] = 0;

	ec_read_sequence(BAT_MODEL_NAME_ADDR,
					data->bat_model_name,
					BAT_MODEL_NAME_LEN);
	data->bat_model_name[BAT_MODEL_NAME_LEN] = 0;

	scnprintf(data->bat_serial_number, BAT_SERIAL_NUMBER_LEN + 1, "%d",
				ec_read_u16(BAT_SERIAL_NUMBER_ADDR));
}