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
struct is31fl319x_chip {int /*<<< orphan*/  lock; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct is31fl319x_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is31fl319x_remove(struct i2c_client *client)
{
	struct is31fl319x_chip *is31 = i2c_get_clientdata(client);

	mutex_destroy(&is31->lock);
	return 0;
}