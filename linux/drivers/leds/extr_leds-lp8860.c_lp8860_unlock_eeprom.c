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
struct lp8860_led {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP8860_EEPROM_CODE_1 ; 
 int /*<<< orphan*/  LP8860_EEPROM_CODE_2 ; 
 int /*<<< orphan*/  LP8860_EEPROM_CODE_3 ; 
 int /*<<< orphan*/  LP8860_EEPROM_UNLOCK ; 
 int /*<<< orphan*/  LP8860_LOCK_EEPROM ; 
 int LP8860_UNLOCK_EEPROM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp8860_unlock_eeprom(struct lp8860_led *led, int lock)
{
	int ret;

	mutex_lock(&led->lock);

	if (lock == LP8860_UNLOCK_EEPROM) {
		ret = regmap_write(led->regmap,
			LP8860_EEPROM_UNLOCK,
			LP8860_EEPROM_CODE_1);
		if (ret) {
			dev_err(&led->client->dev, "EEPROM Unlock failed\n");
			goto out;
		}

		ret = regmap_write(led->regmap,
			LP8860_EEPROM_UNLOCK,
			LP8860_EEPROM_CODE_2);
		if (ret) {
			dev_err(&led->client->dev, "EEPROM Unlock failed\n");
			goto out;
		}
		ret = regmap_write(led->regmap,
			LP8860_EEPROM_UNLOCK,
			LP8860_EEPROM_CODE_3);
		if (ret) {
			dev_err(&led->client->dev, "EEPROM Unlock failed\n");
			goto out;
		}
	} else {
		ret = regmap_write(led->regmap,
			LP8860_EEPROM_UNLOCK,
			LP8860_LOCK_EEPROM);
	}

out:
	mutex_unlock(&led->lock);
	return ret;
}