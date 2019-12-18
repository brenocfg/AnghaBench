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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct kv_power_info {TYPE_1__* graphics_level; } ;
struct atom_clock_dividers {scalar_t__ post_div; } ;
struct TYPE_2__ {int /*<<< orphan*/  SclkFrequency; scalar_t__ SclkDid; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int /*<<< orphan*/  cpu_to_be32 (size_t) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,size_t,int,struct atom_clock_dividers*) ; 

__attribute__((used)) static int kv_set_divider_value(struct radeon_device *rdev,
				u32 index, u32 sclk)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	struct atom_clock_dividers dividers;
	int ret;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     sclk, false, &dividers);
	if (ret)
		return ret;

	pi->graphics_level[index].SclkDid = (u8)dividers.post_div;
	pi->graphics_level[index].SclkFrequency = cpu_to_be32(sclk);

	return 0;
}