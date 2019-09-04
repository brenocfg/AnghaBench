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
struct qt1070_data {int /*<<< orphan*/  input; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct qt1070_data*) ; 
 struct qt1070_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qt1070_data*) ; 

__attribute__((used)) static int qt1070_remove(struct i2c_client *client)
{
	struct qt1070_data *data = i2c_get_clientdata(client);

	/* Release IRQ */
	free_irq(client->irq, data);

	input_unregister_device(data->input);
	kfree(data);

	return 0;
}