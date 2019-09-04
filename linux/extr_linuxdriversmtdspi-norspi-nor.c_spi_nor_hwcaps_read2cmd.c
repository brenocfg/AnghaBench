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
#define  SNOR_CMD_READ 157 
#define  SNOR_CMD_READ_1_1_1_DTR 156 
#define  SNOR_CMD_READ_1_1_2 155 
#define  SNOR_CMD_READ_1_1_4 154 
#define  SNOR_CMD_READ_1_1_8 153 
#define  SNOR_CMD_READ_1_2_2 152 
#define  SNOR_CMD_READ_1_2_2_DTR 151 
#define  SNOR_CMD_READ_1_4_4 150 
#define  SNOR_CMD_READ_1_4_4_DTR 149 
#define  SNOR_CMD_READ_1_8_8 148 
#define  SNOR_CMD_READ_1_8_8_DTR 147 
#define  SNOR_CMD_READ_2_2_2 146 
#define  SNOR_CMD_READ_4_4_4 145 
#define  SNOR_CMD_READ_8_8_8 144 
#define  SNOR_CMD_READ_FAST 143 
#define  SNOR_HWCAPS_READ 142 
#define  SNOR_HWCAPS_READ_1_1_1_DTR 141 
#define  SNOR_HWCAPS_READ_1_1_2 140 
#define  SNOR_HWCAPS_READ_1_1_4 139 
#define  SNOR_HWCAPS_READ_1_1_8 138 
#define  SNOR_HWCAPS_READ_1_2_2 137 
#define  SNOR_HWCAPS_READ_1_2_2_DTR 136 
#define  SNOR_HWCAPS_READ_1_4_4 135 
#define  SNOR_HWCAPS_READ_1_4_4_DTR 134 
#define  SNOR_HWCAPS_READ_1_8_8 133 
#define  SNOR_HWCAPS_READ_1_8_8_DTR 132 
#define  SNOR_HWCAPS_READ_2_2_2 131 
#define  SNOR_HWCAPS_READ_4_4_4 130 
#define  SNOR_HWCAPS_READ_8_8_8 129 
#define  SNOR_HWCAPS_READ_FAST 128 
 int spi_nor_hwcaps2cmd (int /*<<< orphan*/ ,int const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_nor_hwcaps_read2cmd(u32 hwcaps)
{
	static const int hwcaps_read2cmd[][2] = {
		{ SNOR_HWCAPS_READ,		SNOR_CMD_READ },
		{ SNOR_HWCAPS_READ_FAST,	SNOR_CMD_READ_FAST },
		{ SNOR_HWCAPS_READ_1_1_1_DTR,	SNOR_CMD_READ_1_1_1_DTR },
		{ SNOR_HWCAPS_READ_1_1_2,	SNOR_CMD_READ_1_1_2 },
		{ SNOR_HWCAPS_READ_1_2_2,	SNOR_CMD_READ_1_2_2 },
		{ SNOR_HWCAPS_READ_2_2_2,	SNOR_CMD_READ_2_2_2 },
		{ SNOR_HWCAPS_READ_1_2_2_DTR,	SNOR_CMD_READ_1_2_2_DTR },
		{ SNOR_HWCAPS_READ_1_1_4,	SNOR_CMD_READ_1_1_4 },
		{ SNOR_HWCAPS_READ_1_4_4,	SNOR_CMD_READ_1_4_4 },
		{ SNOR_HWCAPS_READ_4_4_4,	SNOR_CMD_READ_4_4_4 },
		{ SNOR_HWCAPS_READ_1_4_4_DTR,	SNOR_CMD_READ_1_4_4_DTR },
		{ SNOR_HWCAPS_READ_1_1_8,	SNOR_CMD_READ_1_1_8 },
		{ SNOR_HWCAPS_READ_1_8_8,	SNOR_CMD_READ_1_8_8 },
		{ SNOR_HWCAPS_READ_8_8_8,	SNOR_CMD_READ_8_8_8 },
		{ SNOR_HWCAPS_READ_1_8_8_DTR,	SNOR_CMD_READ_1_8_8_DTR },
	};

	return spi_nor_hwcaps2cmd(hwcaps, hwcaps_read2cmd,
				  ARRAY_SIZE(hwcaps_read2cmd));
}