#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct adt7475_data {int has_voltage; scalar_t__ has_vid; scalar_t__ has_pwm2; scalar_t__ has_fan4; } ;

/* Variables and functions */
 int /*<<< orphan*/  adt7475_attr_group ; 
 int /*<<< orphan*/  fan4_attr_group ; 
 int /*<<< orphan*/  in0_attr_group ; 
 int /*<<< orphan*/  in3_attr_group ; 
 int /*<<< orphan*/  in4_attr_group ; 
 int /*<<< orphan*/  in5_attr_group ; 
 int /*<<< orphan*/  pwm2_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vid_attr_group ; 

__attribute__((used)) static void adt7475_remove_files(struct i2c_client *client,
				 struct adt7475_data *data)
{
	sysfs_remove_group(&client->dev.kobj, &adt7475_attr_group);
	if (data->has_fan4)
		sysfs_remove_group(&client->dev.kobj, &fan4_attr_group);
	if (data->has_pwm2)
		sysfs_remove_group(&client->dev.kobj, &pwm2_attr_group);
	if (data->has_voltage & (1 << 0))
		sysfs_remove_group(&client->dev.kobj, &in0_attr_group);
	if (data->has_voltage & (1 << 3))
		sysfs_remove_group(&client->dev.kobj, &in3_attr_group);
	if (data->has_voltage & (1 << 4))
		sysfs_remove_group(&client->dev.kobj, &in4_attr_group);
	if (data->has_voltage & (1 << 5))
		sysfs_remove_group(&client->dev.kobj, &in5_attr_group);
	if (data->has_vid)
		sysfs_remove_group(&client->dev.kobj, &vid_attr_group);
}