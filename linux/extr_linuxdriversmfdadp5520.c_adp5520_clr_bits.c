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
typedef  int uint8_t ;
struct device {int dummy; } ;
struct adp5520_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int __adp5520_read (int /*<<< orphan*/ ,int,int*) ; 
 int __adp5520_write (int /*<<< orphan*/ ,int,int) ; 
 struct adp5520_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int adp5520_clr_bits(struct device *dev, int reg, uint8_t bit_mask)
{
	struct adp5520_chip *chip = dev_get_drvdata(dev);
	uint8_t reg_val;
	int ret;

	mutex_lock(&chip->lock);

	ret = __adp5520_read(chip->client, reg, &reg_val);

	if (!ret && (reg_val & bit_mask)) {
		reg_val &= ~bit_mask;
		ret = __adp5520_write(chip->client, reg, reg_val);
	}

	mutex_unlock(&chip->lock);
	return ret;
}