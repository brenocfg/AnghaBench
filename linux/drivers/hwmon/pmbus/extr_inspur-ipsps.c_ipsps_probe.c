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
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipsps_info ; 
 int /*<<< orphan*/  ipsps_pdata ; 
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipsps_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	client->dev.platform_data = &ipsps_pdata;
	return pmbus_do_probe(client, id, &ipsps_info);
}