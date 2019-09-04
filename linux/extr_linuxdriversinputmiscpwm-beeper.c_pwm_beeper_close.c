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
struct pwm_beeper {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct pwm_beeper* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  pwm_beeper_stop (struct pwm_beeper*) ; 

__attribute__((used)) static void pwm_beeper_close(struct input_dev *input)
{
	struct pwm_beeper *beeper = input_get_drvdata(input);

	pwm_beeper_stop(beeper);
}