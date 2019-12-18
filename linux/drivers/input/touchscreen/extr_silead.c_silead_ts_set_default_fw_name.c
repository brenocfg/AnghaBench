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
struct silead_ts_data {int /*<<< orphan*/  fw_name; } ;
struct i2c_device_id {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int silead_ts_set_default_fw_name(struct silead_ts_data *data,
					 const struct i2c_device_id *id)
{
	snprintf(data->fw_name, sizeof(data->fw_name),
		 "silead/%s.fw", id->name);
	return 0;
}