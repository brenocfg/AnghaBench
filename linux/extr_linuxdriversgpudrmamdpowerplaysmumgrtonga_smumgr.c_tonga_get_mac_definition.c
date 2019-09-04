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
 int SMU72_MAX_ENTRIES_SMIO ; 
 int SMU72_MAX_LEVELS_GRAPHICS ; 
 int SMU72_MAX_LEVELS_LINK ; 
 int SMU72_MAX_LEVELS_MEMORY ; 
 int SMU72_MAX_LEVELS_MVDD ; 
 int SMU72_MAX_LEVELS_VDDC ; 
 int SMU72_MAX_LEVELS_VDDCI ; 
 int SMU72_MAX_LEVELS_VDDGFX ; 
#define  SMU_MAX_ENTRIES_SMIO 135 
#define  SMU_MAX_LEVELS_GRAPHICS 134 
#define  SMU_MAX_LEVELS_LINK 133 
#define  SMU_MAX_LEVELS_MEMORY 132 
#define  SMU_MAX_LEVELS_MVDD 131 
#define  SMU_MAX_LEVELS_VDDC 130 
#define  SMU_MAX_LEVELS_VDDCI 129 
#define  SMU_MAX_LEVELS_VDDGFX 128 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static uint32_t tonga_get_mac_definition(uint32_t value)
{
	switch (value) {
	case SMU_MAX_LEVELS_GRAPHICS:
		return SMU72_MAX_LEVELS_GRAPHICS;
	case SMU_MAX_LEVELS_MEMORY:
		return SMU72_MAX_LEVELS_MEMORY;
	case SMU_MAX_LEVELS_LINK:
		return SMU72_MAX_LEVELS_LINK;
	case SMU_MAX_ENTRIES_SMIO:
		return SMU72_MAX_ENTRIES_SMIO;
	case SMU_MAX_LEVELS_VDDC:
		return SMU72_MAX_LEVELS_VDDC;
	case SMU_MAX_LEVELS_VDDGFX:
		return SMU72_MAX_LEVELS_VDDGFX;
	case SMU_MAX_LEVELS_VDDCI:
		return SMU72_MAX_LEVELS_VDDCI;
	case SMU_MAX_LEVELS_MVDD:
		return SMU72_MAX_LEVELS_MVDD;
	}
	pr_warn("can't get the mac value %x\n", value);

	return 0;
}