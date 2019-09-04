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
struct pm80x_chip {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_irq_exit_805 (struct pm80x_chip*) ; 
 struct pm80x_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm80x_deinit () ; 

__attribute__((used)) static int pm805_remove(struct i2c_client *client)
{
	struct pm80x_chip *chip = i2c_get_clientdata(client);

	mfd_remove_devices(chip->dev);
	device_irq_exit_805(chip);

	pm80x_deinit();

	return 0;
}