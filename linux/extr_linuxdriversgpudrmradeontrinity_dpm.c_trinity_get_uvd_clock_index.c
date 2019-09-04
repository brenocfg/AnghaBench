#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* uvd_clock_table_entries; } ;
struct trinity_power_info {TYPE_2__ sys_info; } ;
struct radeon_ps {scalar_t__ vclk; scalar_t__ dclk; } ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ vclk; scalar_t__ dclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 

__attribute__((used)) static u32 trinity_get_uvd_clock_index(struct radeon_device *rdev,
				       struct radeon_ps *rps)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	u32 i = 0;

	for (i = 0; i < 4; i++) {
		if ((rps->vclk == pi->sys_info.uvd_clock_table_entries[i].vclk) &&
		    (rps->dclk == pi->sys_info.uvd_clock_table_entries[i].dclk))
		    break;
	}

	if (i >= 4) {
		DRM_ERROR("UVD clock index not found!\n");
		i = 3;
	}
	return i;
}