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
typedef  int /*<<< orphan*/  modes ;
struct TYPE_2__ {scalar_t__* advertised; } ;

/* Variables and functions */
 size_t MLX5E_EXT_LINK_MODES_NUMBER ; 
 size_t MLX5E_PROT_MASK (size_t) ; 
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int /*<<< orphan*/  bitmap_and (unsigned long*,scalar_t__*,unsigned long const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ptys2ext_ethtool_table ; 

__attribute__((used)) static u32 mlx5e_ethtool2ptys_ext_adver_link(const unsigned long *link_modes)
{
	u32 i, ptys_modes = 0;
	unsigned long modes[2];

	for (i = 0; i < MLX5E_EXT_LINK_MODES_NUMBER; ++i) {
		if (*ptys2ext_ethtool_table[i].advertised == 0)
			continue;
		memset(modes, 0, sizeof(modes));
		bitmap_and(modes, ptys2ext_ethtool_table[i].advertised,
			   link_modes, __ETHTOOL_LINK_MODE_MASK_NBITS);

		if (modes[0] == ptys2ext_ethtool_table[i].advertised[0] &&
		    modes[1] == ptys2ext_ethtool_table[i].advertised[1])
			ptys_modes |= MLX5E_PROT_MASK(i);
	}
	return ptys_modes;
}