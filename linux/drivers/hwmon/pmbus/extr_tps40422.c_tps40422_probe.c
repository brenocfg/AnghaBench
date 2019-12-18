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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tps40422_info ; 

__attribute__((used)) static int tps40422_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	return pmbus_do_probe(client, id, &tps40422_info);
}