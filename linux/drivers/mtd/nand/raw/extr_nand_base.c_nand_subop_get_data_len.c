#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nand_subop {int ninstrs; int last_instr_end_off; TYPE_3__* instrs; } ;
struct TYPE_4__ {int len; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__ ctx; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  nand_instr_is_data (TYPE_3__*) ; 
 int nand_subop_get_data_start_off (struct nand_subop const*,unsigned int) ; 
 int /*<<< orphan*/  nand_subop_instr_is_valid (struct nand_subop const*,unsigned int) ; 

unsigned int nand_subop_get_data_len(const struct nand_subop *subop,
				     unsigned int instr_idx)
{
	int start_off = 0, end_off;

	if (WARN_ON(!nand_subop_instr_is_valid(subop, instr_idx) ||
		    !nand_instr_is_data(&subop->instrs[instr_idx])))
		return 0;

	start_off = nand_subop_get_data_start_off(subop, instr_idx);

	if (instr_idx == subop->ninstrs - 1 &&
	    subop->last_instr_end_off)
		end_off = subop->last_instr_end_off;
	else
		end_off = subop->instrs[instr_idx].ctx.data.len;

	return end_off - start_off;
}