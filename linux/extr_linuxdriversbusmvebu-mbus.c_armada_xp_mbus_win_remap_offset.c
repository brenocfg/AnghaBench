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

/* Variables and functions */
 unsigned int MVEBU_MBUS_NO_REMAP ; 
 unsigned int WIN_REMAP_LO_OFF ; 
 unsigned int generic_mbus_win_cfg_offset (int) ; 

__attribute__((used)) static unsigned int armada_xp_mbus_win_remap_offset(int win)
{
	if (win < 8)
		return generic_mbus_win_cfg_offset(win);
	else if (win == 13)
		return 0xF0 - WIN_REMAP_LO_OFF;
	else
		return MVEBU_MBUS_NO_REMAP;
}