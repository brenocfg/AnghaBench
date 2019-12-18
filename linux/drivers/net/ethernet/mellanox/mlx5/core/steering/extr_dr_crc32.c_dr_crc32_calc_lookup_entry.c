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
typedef  size_t u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void dr_crc32_calc_lookup_entry(u32 (*tbl)[256], u8 i, u8 j)
{
	tbl[i][j] = (tbl[i - 1][j] >> 8) ^ tbl[0][tbl[i - 1][j] & 0xff];
}