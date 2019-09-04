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

/* Variables and functions */
 int C_SW0 ; 
 scalar_t__ MIPS_CPU_IRQ_BASE ; 
 scalar_t__ MIPS_CPU_RTLX_IRQ ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 int read_c0_cause () ; 
 int read_c0_status () ; 

__attribute__((used)) static void rtlx_dispatch(void)
{
	if (read_c0_cause() & read_c0_status() & C_SW0)
		do_IRQ(MIPS_CPU_IRQ_BASE + MIPS_CPU_RTLX_IRQ);
}