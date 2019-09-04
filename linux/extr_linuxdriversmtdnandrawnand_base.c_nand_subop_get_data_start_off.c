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
struct nand_subop {int /*<<< orphan*/ * instrs; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  nand_instr_is_data (int /*<<< orphan*/ *) ; 
 unsigned int nand_subop_get_start_off (struct nand_subop const*,unsigned int) ; 
 int /*<<< orphan*/  nand_subop_instr_is_valid (struct nand_subop const*,unsigned int) ; 

unsigned int nand_subop_get_data_start_off(const struct nand_subop *subop,
					   unsigned int instr_idx)
{
	if (WARN_ON(!nand_subop_instr_is_valid(subop, instr_idx) ||
		    !nand_instr_is_data(&subop->instrs[instr_idx])))
		return 0;

	return nand_subop_get_start_off(subop, instr_idx);
}