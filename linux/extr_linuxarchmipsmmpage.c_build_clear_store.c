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
 int /*<<< orphan*/  A0 ; 
 int /*<<< orphan*/  ZERO ; 
 scalar_t__ cpu_has_64bit_gp_regs ; 
 scalar_t__ cpu_has_64bit_zero_reg ; 
 int /*<<< orphan*/  uasm_i_sd (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_sw (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_clear_store(u32 **buf, int off)
{
	if (cpu_has_64bit_gp_regs || cpu_has_64bit_zero_reg) {
		uasm_i_sd(buf, ZERO, off, A0);
	} else {
		uasm_i_sw(buf, ZERO, off, A0);
	}
}