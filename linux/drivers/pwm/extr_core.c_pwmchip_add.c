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

/* Variables and functions */
 int /*<<< orphan*/  PWM_POLARITY_NORMAL ; 
 int pwmchip_add_with_polarity (struct pwm_chip*,int /*<<< orphan*/ ) ; 

int pwmchip_add(struct pwm_chip *chip)
{
	return pwmchip_add_with_polarity(chip, PWM_POLARITY_NORMAL);
}