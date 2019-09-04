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
typedef  int u32 ;
struct module {int dummy; } ;
typedef  int s32 ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */

__attribute__((used)) static int apply_r_riscv_lo12_s_rela(struct module *me, u32 *location,
				     Elf_Addr v)
{
	/* Skip medlow checking because of filtering by HI20 already */
	s32 hi20 = ((s32)v + 0x800) & 0xfffff000;
	s32 lo12 = ((s32)v - hi20);
	u32 imm11_5 = (lo12 & 0xfe0) << (31 - 11);
	u32 imm4_0 = (lo12 & 0x1f) << (11 - 4);
	*location = (*location & 0x1fff07f) | imm11_5 | imm4_0;
	return 0;
}