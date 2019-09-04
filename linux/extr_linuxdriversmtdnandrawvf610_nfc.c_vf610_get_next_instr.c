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
struct nand_subop {int ninstrs; struct nand_op_instr const* instrs; } ;
struct nand_op_instr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct nand_op_instr *
vf610_get_next_instr(const struct nand_subop *subop, int *op_id)
{
	if (*op_id + 1 >= subop->ninstrs)
		return NULL;

	(*op_id)++;

	return &subop->instrs[*op_id];
}