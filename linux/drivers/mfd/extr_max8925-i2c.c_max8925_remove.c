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
struct max8925_chip {int /*<<< orphan*/  rtc; int /*<<< orphan*/  adc; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct max8925_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8925_device_exit (struct max8925_chip*) ; 

__attribute__((used)) static int max8925_remove(struct i2c_client *client)
{
	struct max8925_chip *chip = i2c_get_clientdata(client);

	max8925_device_exit(chip);
	i2c_unregister_device(chip->adc);
	i2c_unregister_device(chip->rtc);
	return 0;
}