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
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct adp5589_kpad {int /*<<< orphan*/  input; TYPE_1__* var; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reg ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5589_GENERAL_CFG ; 
 int /*<<< orphan*/  adp5589_gpio_remove (struct adp5589_kpad*) ; 
 int /*<<< orphan*/  adp5589_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adp5589_kpad*) ; 
 struct adp5589_kpad* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct adp5589_kpad*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adp5589_remove(struct i2c_client *client)
{
	struct adp5589_kpad *kpad = i2c_get_clientdata(client);

	adp5589_write(client, kpad->var->reg(ADP5589_GENERAL_CFG), 0);
	free_irq(client->irq, kpad);
	input_unregister_device(kpad->input);
	adp5589_gpio_remove(kpad);
	kfree(kpad);

	return 0;
}