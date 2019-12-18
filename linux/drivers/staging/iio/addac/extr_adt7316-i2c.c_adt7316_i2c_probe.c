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
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct adt7316_bus {int /*<<< orphan*/  multi_write; int /*<<< orphan*/  multi_read; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  irq; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  adt7316_i2c_multi_read ; 
 int /*<<< orphan*/  adt7316_i2c_multi_write ; 
 int /*<<< orphan*/  adt7316_i2c_read ; 
 int /*<<< orphan*/  adt7316_i2c_write ; 
 int adt7316_probe (int /*<<< orphan*/ *,struct adt7316_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adt7316_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct adt7316_bus bus = {
		.client = client,
		.irq = client->irq,
		.read = adt7316_i2c_read,
		.write = adt7316_i2c_write,
		.multi_read = adt7316_i2c_multi_read,
		.multi_write = adt7316_i2c_multi_write,
	};

	return adt7316_probe(&client->dev, &bus, id->name);
}