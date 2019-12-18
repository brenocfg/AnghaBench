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
struct sky2_hw {int flags; } ;

/* Variables and functions */
 int SKY2_HW_GIGABIT ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 scalar_t__ sky2_is_copper (struct sky2_hw const*) ; 

__attribute__((used)) static u32 sky2_supported_modes(const struct sky2_hw *hw)
{
	if (sky2_is_copper(hw)) {
		u32 modes = SUPPORTED_10baseT_Half
			| SUPPORTED_10baseT_Full
			| SUPPORTED_100baseT_Half
			| SUPPORTED_100baseT_Full;

		if (hw->flags & SKY2_HW_GIGABIT)
			modes |= SUPPORTED_1000baseT_Half
				| SUPPORTED_1000baseT_Full;
		return modes;
	} else
		return SUPPORTED_1000baseT_Half
			| SUPPORTED_1000baseT_Full;
}