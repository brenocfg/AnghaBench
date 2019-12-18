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
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct berlin_pwm_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct berlin_pwm_channel*) ; 
 struct berlin_pwm_channel* pwm_get_chip_data (struct pwm_device*) ; 

__attribute__((used)) static void berlin_pwm_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct berlin_pwm_channel *channel = pwm_get_chip_data(pwm);

	kfree(channel);
}