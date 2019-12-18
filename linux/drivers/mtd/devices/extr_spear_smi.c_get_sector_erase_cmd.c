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
typedef  int u8 ;
typedef  int u32 ;
struct spear_snor_flash {int erase_cmd; } ;

/* Variables and functions */

__attribute__((used)) static inline u32
get_sector_erase_cmd(struct spear_snor_flash *flash, u32 offset)
{
	u32 cmd;
	u8 *x = (u8 *)&cmd;

	x[0] = flash->erase_cmd;
	x[1] = offset >> 16;
	x[2] = offset >> 8;
	x[3] = offset;

	return cmd;
}