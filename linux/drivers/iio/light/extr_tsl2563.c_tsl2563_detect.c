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
struct tsl2563_chip {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int tsl2563_get_power (struct tsl2563_chip*) ; 
 int tsl2563_set_power (struct tsl2563_chip*,int) ; 

__attribute__((used)) static int tsl2563_detect(struct tsl2563_chip *chip)
{
	int ret;

	ret = tsl2563_set_power(chip, 1);
	if (ret)
		return ret;

	ret = tsl2563_get_power(chip);
	if (ret < 0)
		return ret;

	return ret ? 0 : -ENODEV;
}