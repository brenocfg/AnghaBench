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
 int /*<<< orphan*/  A1 ; 
 scalar_t__ cpu_has_64bit_gp_regs ; 
 int /*<<< orphan*/  uasm_i_ld (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_lw (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_copy_load(u32 **buf, int reg, int off)
{
	if (cpu_has_64bit_gp_regs) {
		uasm_i_ld(buf, reg, off, A1);
	} else {
		uasm_i_lw(buf, reg, off, A1);
	}
}