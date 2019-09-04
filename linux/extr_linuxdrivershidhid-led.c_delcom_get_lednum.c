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
struct hidled_led {TYPE_1__* rgb; } ;
struct TYPE_2__ {struct hidled_led const green; struct hidled_led const red; } ;

/* Variables and functions */
 int DELCOM_BLUE_LED ; 
 int DELCOM_GREEN_LED ; 
 int DELCOM_RED_LED ; 

__attribute__((used)) static inline int delcom_get_lednum(const struct hidled_led *led)
{
	if (led == &led->rgb->red)
		return DELCOM_RED_LED;
	else if (led == &led->rgb->green)
		return DELCOM_GREEN_LED;
	else
		return DELCOM_BLUE_LED;
}