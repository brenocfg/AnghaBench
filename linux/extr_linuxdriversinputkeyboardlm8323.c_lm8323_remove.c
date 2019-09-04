#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lm8323_chip {TYPE_1__* pwm; TYPE_2__* client; int /*<<< orphan*/  idev; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdev; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_disable_kp ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct lm8323_chip*) ; 
 struct lm8323_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lm8323_chip*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm8323_remove(struct i2c_client *client)
{
	struct lm8323_chip *lm = i2c_get_clientdata(client);
	int i;

	disable_irq_wake(client->irq);
	free_irq(client->irq, lm);

	input_unregister_device(lm->idev);

	device_remove_file(&lm->client->dev, &dev_attr_disable_kp);

	for (i = 0; i < 3; i++)
		if (lm->pwm[i].enabled)
			led_classdev_unregister(&lm->pwm[i].cdev);

	kfree(lm);

	return 0;
}