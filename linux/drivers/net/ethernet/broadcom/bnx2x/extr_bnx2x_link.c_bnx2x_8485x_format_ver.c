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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int bnx2x_3_seq_format_ver (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_8485x_format_ver(u32 raw_ver, u8 *str, u16 *len)
{
	u32 num;

	num = ((raw_ver & 0xF80) >> 7) << 16 | ((raw_ver & 0x7F) << 8) |
	      ((raw_ver & 0xF000) >> 12);
	return bnx2x_3_seq_format_ver(num, str, len);
}