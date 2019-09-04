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
struct linux_prom_registers {int dummy; } ;

/* Variables and functions */
 scalar_t__ num_obio_ranges ; 
 int /*<<< orphan*/  prom_adjust_regs (struct linux_prom_registers*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  promlib_obio_ranges ; 

void prom_apply_obio_ranges(struct linux_prom_registers *regs, int nregs)
{
	if (num_obio_ranges)
		prom_adjust_regs(regs, nregs, promlib_obio_ranges, num_obio_ranges);
}