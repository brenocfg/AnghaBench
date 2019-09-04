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
struct pwm_beeper {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_beeper_off (struct pwm_beeper*) ; 

__attribute__((used)) static void pwm_beeper_stop(struct pwm_beeper *beeper)
{
	cancel_work_sync(&beeper->work);
	pwm_beeper_off(beeper);
}