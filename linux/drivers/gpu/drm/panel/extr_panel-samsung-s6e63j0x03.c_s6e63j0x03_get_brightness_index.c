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
 unsigned int MAX_BRIGHTNESS ; 
 unsigned int NUM_GAMMA_STEPS ; 

__attribute__((used)) static unsigned int s6e63j0x03_get_brightness_index(unsigned int brightness)
{
	unsigned int index;

	index = brightness / (MAX_BRIGHTNESS / NUM_GAMMA_STEPS);

	if (index >= NUM_GAMMA_STEPS)
		index = NUM_GAMMA_STEPS - 1;

	return index;
}