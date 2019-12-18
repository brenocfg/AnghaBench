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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int const**) ; 
#define  SNOR_CMD_PP 141 
#define  SNOR_CMD_PP_1_1_4 140 
#define  SNOR_CMD_PP_1_1_8 139 
#define  SNOR_CMD_PP_1_4_4 138 
#define  SNOR_CMD_PP_1_8_8 137 
#define  SNOR_CMD_PP_4_4_4 136 
#define  SNOR_CMD_PP_8_8_8 135 
#define  SNOR_HWCAPS_PP 134 
#define  SNOR_HWCAPS_PP_1_1_4 133 
#define  SNOR_HWCAPS_PP_1_1_8 132 
#define  SNOR_HWCAPS_PP_1_4_4 131 
#define  SNOR_HWCAPS_PP_1_8_8 130 
#define  SNOR_HWCAPS_PP_4_4_4 129 
#define  SNOR_HWCAPS_PP_8_8_8 128 
 int spi_nor_hwcaps2cmd (int /*<<< orphan*/ ,int const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_nor_hwcaps_pp2cmd(u32 hwcaps)
{
	static const int hwcaps_pp2cmd[][2] = {
		{ SNOR_HWCAPS_PP,		SNOR_CMD_PP },
		{ SNOR_HWCAPS_PP_1_1_4,		SNOR_CMD_PP_1_1_4 },
		{ SNOR_HWCAPS_PP_1_4_4,		SNOR_CMD_PP_1_4_4 },
		{ SNOR_HWCAPS_PP_4_4_4,		SNOR_CMD_PP_4_4_4 },
		{ SNOR_HWCAPS_PP_1_1_8,		SNOR_CMD_PP_1_1_8 },
		{ SNOR_HWCAPS_PP_1_8_8,		SNOR_CMD_PP_1_8_8 },
		{ SNOR_HWCAPS_PP_8_8_8,		SNOR_CMD_PP_8_8_8 },
	};

	return spi_nor_hwcaps2cmd(hwcaps, hwcaps_pp2cmd,
				  ARRAY_SIZE(hwcaps_pp2cmd));
}