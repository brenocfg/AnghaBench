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
struct pwm_chip {int dummy; } ;
struct platform_device {int dummy; } ;
struct cros_ec_pwm_device {struct pwm_chip chip; } ;

/* Variables and functions */
 struct cros_ec_pwm_device* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (struct pwm_chip*) ; 

__attribute__((used)) static int cros_ec_pwm_remove(struct platform_device *dev)
{
	struct cros_ec_pwm_device *ec_pwm = platform_get_drvdata(dev);
	struct pwm_chip *chip = &ec_pwm->chip;

	return pwmchip_remove(chip);
}