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
typedef  enum ethtool_report { ____Placeholder_ethtool_report } ethtool_report ;

/* Variables and functions */
 int MLX4_LINK_MODES_SZ ; 
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 scalar_t__ bitmap_intersects (int /*<<< orphan*/ ,unsigned long const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptys2ethtool_link_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ptys2ethtool_map ; 

__attribute__((used)) static u32 ethtool2ptys_link_modes(const unsigned long *link_modes,
				   enum ethtool_report report)
{
	int i;
	u32 ptys_modes = 0;

	for (i = 0; i < MLX4_LINK_MODES_SZ; i++) {
		if (bitmap_intersects(
			    ptys2ethtool_link_mode(&ptys2ethtool_map[i],
						   report),
			    link_modes,
			    __ETHTOOL_LINK_MODE_MASK_NBITS))
			ptys_modes |= 1 << i;
	}
	return ptys_modes;
}