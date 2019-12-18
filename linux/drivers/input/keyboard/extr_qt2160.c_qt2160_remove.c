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
struct qt2160_data {int /*<<< orphan*/  input; int /*<<< orphan*/  dwork; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct qt2160_data*) ; 
 struct qt2160_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qt2160_data*) ; 
 int /*<<< orphan*/  qt2160_unregister_leds (struct qt2160_data*) ; 

__attribute__((used)) static int qt2160_remove(struct i2c_client *client)
{
	struct qt2160_data *qt2160 = i2c_get_clientdata(client);

	qt2160_unregister_leds(qt2160);

	/* Release IRQ so no queue will be scheduled */
	if (client->irq)
		free_irq(client->irq, qt2160);

	cancel_delayed_work_sync(&qt2160->dwork);

	input_unregister_device(qt2160->input);
	kfree(qt2160);

	return 0;
}