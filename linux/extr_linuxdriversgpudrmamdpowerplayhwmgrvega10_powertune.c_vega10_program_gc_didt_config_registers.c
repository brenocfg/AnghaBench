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
typedef  int uint32_t ;
struct vega10_didt_config_reg {int offset; int mask; int value; int shift; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int cgs_read_register (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vega10_program_gc_didt_config_registers(struct pp_hwmgr *hwmgr, const struct vega10_didt_config_reg *config_regs)
{
	uint32_t data;

	while (config_regs->offset != 0xFFFFFFFF) {
		data = cgs_read_register(hwmgr->device, config_regs->offset);
		data &= ~config_regs->mask;
		data |= ((config_regs->value << config_regs->shift) & config_regs->mask);
		cgs_write_register(hwmgr->device, config_regs->offset, data);
		config_regs++;
	}

	return 0;
}