#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPANION (TYPE_1__*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct i2c_client*) ; 
 int /*<<< orphan*/  OF_POPULATED ; 
 int /*<<< orphan*/  acpi_device_clear_enumerated (scalar_t__) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_clear_flag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (scalar_t__) ; 

void i2c_unregister_device(struct i2c_client *client)
{
	if (IS_ERR_OR_NULL(client))
		return;

	if (client->dev.of_node) {
		of_node_clear_flag(client->dev.of_node, OF_POPULATED);
		of_node_put(client->dev.of_node);
	}

	if (ACPI_COMPANION(&client->dev))
		acpi_device_clear_enumerated(ACPI_COMPANION(&client->dev));
	device_unregister(&client->dev);
}