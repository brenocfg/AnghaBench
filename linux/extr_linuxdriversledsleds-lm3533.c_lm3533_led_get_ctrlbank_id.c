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
struct lm3533_led {int id; } ;

/* Variables and functions */

__attribute__((used)) static inline int lm3533_led_get_ctrlbank_id(struct lm3533_led *led)
{
	return led->id + 2;
}