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
struct synaptics_i2c {int /*<<< orphan*/  input; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct synaptics_i2c*) ; 
 struct synaptics_i2c* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct synaptics_i2c*) ; 
 int /*<<< orphan*/  polling_req ; 

__attribute__((used)) static int synaptics_i2c_remove(struct i2c_client *client)
{
	struct synaptics_i2c *touch = i2c_get_clientdata(client);

	if (!polling_req)
		free_irq(client->irq, touch);

	input_unregister_device(touch->input);
	kfree(touch);

	return 0;
}