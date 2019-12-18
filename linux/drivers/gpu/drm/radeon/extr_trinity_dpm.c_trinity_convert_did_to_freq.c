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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int dentist_vco_freq; } ;
struct trinity_power_info {TYPE_1__ sys_info; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 

__attribute__((used)) static u32 trinity_convert_did_to_freq(struct radeon_device *rdev, u8 did)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	u32 divider;

	if (did >= 8 && did <= 0x3f)
		divider = did * 25;
	else if (did > 0x3f && did <= 0x5f)
		divider = (did - 64) * 50 + 1600;
	else if (did > 0x5f && did <= 0x7e)
		divider = (did - 96) * 100 + 3200;
	else if (did == 0x7f)
		divider = 128 * 100;
	else
		return 10000;

	return ((pi->sys_info.dentist_vco_freq * 100) + (divider - 1)) / divider;
}