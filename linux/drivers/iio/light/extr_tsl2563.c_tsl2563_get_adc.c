#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct tsl2563_chip {int /*<<< orphan*/  poweroff_work; int /*<<< orphan*/  int_enabled; TYPE_1__* gainlevel; void* data1; void* data0; scalar_t__ suspended; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gaintime; } ;

/* Variables and functions */
 int HZ ; 
 int TSL2563_CMD ; 
 int TSL2563_REG_DATA0LOW ; 
 int TSL2563_REG_DATA1LOW ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int tsl2563_adjust_gainlevel (struct tsl2563_chip*,int) ; 
 int tsl2563_configure (struct tsl2563_chip*) ; 
 int /*<<< orphan*/  tsl2563_get_power (struct tsl2563_chip*) ; 
 void* tsl2563_normalize_adc (int,int /*<<< orphan*/ ) ; 
 int tsl2563_set_power (struct tsl2563_chip*,int) ; 
 int /*<<< orphan*/  tsl2563_wait_adc (struct tsl2563_chip*) ; 

__attribute__((used)) static int tsl2563_get_adc(struct tsl2563_chip *chip)
{
	struct i2c_client *client = chip->client;
	u16 adc0, adc1;
	int retry = 1;
	int ret = 0;

	if (chip->suspended)
		goto out;

	if (!chip->int_enabled) {
		cancel_delayed_work(&chip->poweroff_work);

		if (!tsl2563_get_power(chip)) {
			ret = tsl2563_set_power(chip, 1);
			if (ret)
				goto out;
			ret = tsl2563_configure(chip);
			if (ret)
				goto out;
			tsl2563_wait_adc(chip);
		}
	}

	while (retry) {
		ret = i2c_smbus_read_word_data(client,
				TSL2563_CMD | TSL2563_REG_DATA0LOW);
		if (ret < 0)
			goto out;
		adc0 = ret;

		ret = i2c_smbus_read_word_data(client,
				TSL2563_CMD | TSL2563_REG_DATA1LOW);
		if (ret < 0)
			goto out;
		adc1 = ret;

		retry = tsl2563_adjust_gainlevel(chip, adc0);
	}

	chip->data0 = tsl2563_normalize_adc(adc0, chip->gainlevel->gaintime);
	chip->data1 = tsl2563_normalize_adc(adc1, chip->gainlevel->gaintime);

	if (!chip->int_enabled)
		schedule_delayed_work(&chip->poweroff_work, 5 * HZ);

	ret = 0;
out:
	return ret;
}