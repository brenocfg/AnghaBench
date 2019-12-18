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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CISLAND_MAX_DEEPSLEEP_DIVIDER_ID ; 
 scalar_t__ CISLAND_MINIMUM_ENGINE_CLOCK ; 

__attribute__((used)) static u8 ci_get_sleep_divider_id_from_clock(struct radeon_device *rdev,
					     u32 sclk, u32 min_sclk_in_sr)
{
	u32 i;
	u32 tmp;
	u32 min = (min_sclk_in_sr > CISLAND_MINIMUM_ENGINE_CLOCK) ?
		min_sclk_in_sr : CISLAND_MINIMUM_ENGINE_CLOCK;

	if (sclk < min)
		return 0;

	for (i = CISLAND_MAX_DEEPSLEEP_DIVIDER_ID;  ; i--) {
		tmp = sclk / (1 << i);
		if (tmp >= min || i == 0)
			break;
	}

	return (u8)i;
}