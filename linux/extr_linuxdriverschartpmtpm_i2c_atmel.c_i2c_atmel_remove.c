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
struct tpm_chip {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 struct tpm_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  tpm_chip_unregister (struct tpm_chip*) ; 

__attribute__((used)) static int i2c_atmel_remove(struct i2c_client *client)
{
	struct device *dev = &(client->dev);
	struct tpm_chip *chip = dev_get_drvdata(dev);
	tpm_chip_unregister(chip);
	return 0;
}