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
struct i2c_device_id {int /*<<< orphan*/  name; int /*<<< orphan*/  driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad5686_i2c_read ; 
 int /*<<< orphan*/  ad5686_i2c_write ; 
 int ad5686_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5686_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	return ad5686_probe(&i2c->dev, id->driver_data, id->name,
			    ad5686_i2c_write, ad5686_i2c_read);
}