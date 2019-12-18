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
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct adp5588_kpad {int /*<<< orphan*/  input; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG ; 
 int /*<<< orphan*/  adp5588_gpio_remove (struct adp5588_kpad*) ; 
 int /*<<< orphan*/  adp5588_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adp5588_kpad*) ; 
 struct adp5588_kpad* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct adp5588_kpad*) ; 

__attribute__((used)) static int adp5588_remove(struct i2c_client *client)
{
	struct adp5588_kpad *kpad = i2c_get_clientdata(client);

	adp5588_write(client, CFG, 0);
	free_irq(client->irq, kpad);
	cancel_delayed_work_sync(&kpad->work);
	input_unregister_device(kpad->input);
	adp5588_gpio_remove(kpad);
	kfree(kpad);

	return 0;
}