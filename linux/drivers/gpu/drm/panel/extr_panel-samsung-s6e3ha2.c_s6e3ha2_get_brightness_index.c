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
 unsigned int S6E3HA2_MAX_BRIGHTNESS ; 
 int S6E3HA2_NUM_GAMMA_STEPS ; 

__attribute__((used)) static unsigned int s6e3ha2_get_brightness_index(unsigned int brightness)
{
	return (brightness * (S6E3HA2_NUM_GAMMA_STEPS - 1)) /
		S6E3HA2_MAX_BRIGHTNESS;
}