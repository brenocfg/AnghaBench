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
#define  hwmon_chip_alarms 129 
#define  hwmon_chip_update_interval 128 

__attribute__((used)) static umode_t lm90_chip_is_visible(const void *data, u32 attr, int channel)
{
	switch (attr) {
	case hwmon_chip_update_interval:
		return S_IRUGO | S_IWUSR;
	case hwmon_chip_alarms:
		return S_IRUGO;
	default:
		return 0;
	}
}