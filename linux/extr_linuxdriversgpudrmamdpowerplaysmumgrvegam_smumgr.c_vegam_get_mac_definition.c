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
typedef  int uint32_t ;

/* Variables and functions */
 int SMU75_MAX_ENTRIES_SMIO ; 
 int SMU75_MAX_LEVELS_GRAPHICS ; 
 int SMU75_MAX_LEVELS_LINK ; 
 int SMU75_MAX_LEVELS_MEMORY ; 
 int SMU75_MAX_LEVELS_MVDD ; 
 int SMU75_MAX_LEVELS_VDDC ; 
 int SMU75_MAX_LEVELS_VDDCI ; 
 int SMU75_MAX_LEVELS_VDDGFX ; 
 int SMU7_UVD_MCLK_HANDSHAKE_DISABLE ; 
 int SMU7_VCE_MCLK_HANDSHAKE_DISABLE ; 
#define  SMU_MAX_ENTRIES_SMIO 136 
#define  SMU_MAX_LEVELS_GRAPHICS 135 
#define  SMU_MAX_LEVELS_LINK 134 
#define  SMU_MAX_LEVELS_MEMORY 133 
#define  SMU_MAX_LEVELS_MVDD 132 
#define  SMU_MAX_LEVELS_VDDC 131 
#define  SMU_MAX_LEVELS_VDDCI 130 
#define  SMU_MAX_LEVELS_VDDGFX 129 
#define  SMU_UVD_MCLK_HANDSHAKE_DISABLE 128 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static uint32_t vegam_get_mac_definition(uint32_t value)
{
	switch (value) {
	case SMU_MAX_LEVELS_GRAPHICS:
		return SMU75_MAX_LEVELS_GRAPHICS;
	case SMU_MAX_LEVELS_MEMORY:
		return SMU75_MAX_LEVELS_MEMORY;
	case SMU_MAX_LEVELS_LINK:
		return SMU75_MAX_LEVELS_LINK;
	case SMU_MAX_ENTRIES_SMIO:
		return SMU75_MAX_ENTRIES_SMIO;
	case SMU_MAX_LEVELS_VDDC:
		return SMU75_MAX_LEVELS_VDDC;
	case SMU_MAX_LEVELS_VDDGFX:
		return SMU75_MAX_LEVELS_VDDGFX;
	case SMU_MAX_LEVELS_VDDCI:
		return SMU75_MAX_LEVELS_VDDCI;
	case SMU_MAX_LEVELS_MVDD:
		return SMU75_MAX_LEVELS_MVDD;
	case SMU_UVD_MCLK_HANDSHAKE_DISABLE:
		return SMU7_UVD_MCLK_HANDSHAKE_DISABLE |
				SMU7_VCE_MCLK_HANDSHAKE_DISABLE;
	}

	pr_warn("can't get the mac of %x\n", value);
	return 0;
}