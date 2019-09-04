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
struct lm3533_led {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3533_REG_PATTERN_HIGH_TIME_BASE ; 
 int lm3533_led_delay_set (struct lm3533_led*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int lm3533_led_delay_on_set(struct lm3533_led *led, unsigned long *t)
{
	return lm3533_led_delay_set(led, LM3533_REG_PATTERN_HIGH_TIME_BASE, t);
}