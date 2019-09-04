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
struct smiapp_sensor {TYPE_1__* src; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_ident ; 
 int /*<<< orphan*/  dev_attr_nvm ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smiapp_free_controls (struct smiapp_sensor*) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smiapp_cleanup(struct smiapp_sensor *sensor)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);

	device_remove_file(&client->dev, &dev_attr_nvm);
	device_remove_file(&client->dev, &dev_attr_ident);

	smiapp_free_controls(sensor);
}