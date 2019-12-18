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
struct tpic2810 {int /*<<< orphan*/  chip; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct tpic2810* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int tpic2810_remove(struct i2c_client *client)
{
	struct tpic2810 *gpio = i2c_get_clientdata(client);

	gpiochip_remove(&gpio->chip);

	return 0;
}