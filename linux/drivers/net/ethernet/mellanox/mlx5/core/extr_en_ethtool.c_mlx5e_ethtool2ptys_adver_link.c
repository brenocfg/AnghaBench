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
typedef  size_t u32 ;
struct TYPE_2__ {scalar_t__* advertised; } ;

/* Variables and functions */
 size_t MLX5E_LINK_MODES_NUMBER ; 
 size_t MLX5E_PROT_MASK (size_t) ; 
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 scalar_t__ bitmap_intersects (scalar_t__*,unsigned long const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ptys2legacy_ethtool_table ; 

__attribute__((used)) static u32 mlx5e_ethtool2ptys_adver_link(const unsigned long *link_modes)
{
	u32 i, ptys_modes = 0;

	for (i = 0; i < MLX5E_LINK_MODES_NUMBER; ++i) {
		if (*ptys2legacy_ethtool_table[i].advertised == 0)
			continue;
		if (bitmap_intersects(ptys2legacy_ethtool_table[i].advertised,
				      link_modes,
				      __ETHTOOL_LINK_MODE_MASK_NBITS))
			ptys_modes |= MLX5E_PROT_MASK(i);
	}

	return ptys_modes;
}