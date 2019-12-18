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
struct i2c_client {int dummy; } ;
struct an30259a {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 struct an30259a* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int an30259a_remove(struct i2c_client *client)
{
	struct an30259a *chip = i2c_get_clientdata(client);

	mutex_destroy(&chip->mutex);

	return 0;
}