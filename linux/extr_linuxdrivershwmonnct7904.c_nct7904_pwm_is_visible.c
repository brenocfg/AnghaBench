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

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
#define  hwmon_pwm_enable 129 
#define  hwmon_pwm_input 128 

__attribute__((used)) static umode_t nct7904_pwm_is_visible(const void *_data, u32 attr, int channel)
{
	switch (attr) {
	case hwmon_pwm_input:
	case hwmon_pwm_enable:
		return S_IRUGO | S_IWUSR;
	default:
		return 0;
	}
}