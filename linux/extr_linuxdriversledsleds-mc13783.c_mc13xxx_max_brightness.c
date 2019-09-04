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

/* Variables and functions */
 int MC13783_LED_B3 ; 
 int MC13783_LED_KP ; 
 int MC13783_LED_MD ; 
 int MC13783_LED_R1 ; 

__attribute__((used)) static unsigned int mc13xxx_max_brightness(int id)
{
	if (id >= MC13783_LED_MD && id <= MC13783_LED_KP)
		return 0x0f;
	else if (id >= MC13783_LED_R1 && id <= MC13783_LED_B3)
		return 0x1f;

	return 0x3f;
}