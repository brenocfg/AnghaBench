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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct tpm_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  tpm_chip_unregister (struct tpm_chip*) ; 

__attribute__((used)) static int i2c_nuvoton_remove(struct i2c_client *client)
{
	struct tpm_chip *chip = i2c_get_clientdata(client);

	tpm_chip_unregister(chip);
	return 0;
}