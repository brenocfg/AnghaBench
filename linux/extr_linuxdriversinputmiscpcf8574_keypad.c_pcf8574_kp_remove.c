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
struct kp_data {int /*<<< orphan*/  idev; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct kp_data*) ; 
 struct kp_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kp_data*) ; 

__attribute__((used)) static int pcf8574_kp_remove(struct i2c_client *client)
{
	struct kp_data *lp = i2c_get_clientdata(client);

	free_irq(client->irq, lp);

	input_unregister_device(lp->idev);
	kfree(lp);

	return 0;
}