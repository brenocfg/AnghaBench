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
struct lm8333 {int /*<<< orphan*/  input; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct lm8333*) ; 
 struct lm8333* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lm8333*) ; 

__attribute__((used)) static int lm8333_remove(struct i2c_client *client)
{
	struct lm8333 *lm8333 = i2c_get_clientdata(client);

	free_irq(client->irq, lm8333);
	input_unregister_device(lm8333->input);
	kfree(lm8333);

	return 0;
}