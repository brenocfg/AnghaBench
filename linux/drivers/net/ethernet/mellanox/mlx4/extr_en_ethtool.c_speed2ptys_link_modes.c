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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ speed; } ;

/* Variables and functions */
 int MLX4_LINK_MODES_SZ ; 
 TYPE_1__* ptys2ethtool_map ; 

__attribute__((used)) static u32 speed2ptys_link_modes(u32 speed)
{
	int i;
	u32 ptys_modes = 0;

	for (i = 0; i < MLX4_LINK_MODES_SZ; i++) {
		if (ptys2ethtool_map[i].speed == speed)
			ptys_modes |= 1 << i;
	}
	return ptys_modes;
}