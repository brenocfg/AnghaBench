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
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 ci_get_lowest_enabled_level(struct amdgpu_device *adev,
				       u32 level_mask)
{
	u32 level = 0;

	while ((level_mask & (1 << level)) == 0)
		level++;

	return level;
}