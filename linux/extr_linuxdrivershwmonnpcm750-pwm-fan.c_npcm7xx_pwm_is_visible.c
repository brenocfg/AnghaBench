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
typedef  int umode_t ;
typedef  int u32 ;
struct npcm7xx_pwm_fan_data {int /*<<< orphan*/ * pwm_present; } ;

/* Variables and functions */
#define  hwmon_pwm_input 128 

__attribute__((used)) static umode_t npcm7xx_pwm_is_visible(const void *_data, u32 attr, int channel)
{
	const struct npcm7xx_pwm_fan_data *data = _data;

	if (!data->pwm_present[channel])
		return 0;

	switch (attr) {
	case hwmon_pwm_input:
		return 0644;
	default:
		return 0;
	}
}