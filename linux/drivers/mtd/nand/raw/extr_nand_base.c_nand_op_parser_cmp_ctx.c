#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ninstrs; scalar_t__ last_instr_end_off; } ;
struct nand_op_parser_ctx {TYPE_1__ subop; } ;

/* Variables and functions */

__attribute__((used)) static int nand_op_parser_cmp_ctx(const struct nand_op_parser_ctx *a,
				  const struct nand_op_parser_ctx *b)
{
	if (a->subop.ninstrs < b->subop.ninstrs)
		return -1;
	else if (a->subop.ninstrs > b->subop.ninstrs)
		return 1;

	if (a->subop.last_instr_end_off < b->subop.last_instr_end_off)
		return -1;
	else if (a->subop.last_instr_end_off > b->subop.last_instr_end_off)
		return 1;

	return 0;
}