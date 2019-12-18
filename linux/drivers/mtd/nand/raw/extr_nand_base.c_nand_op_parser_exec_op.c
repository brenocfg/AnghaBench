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
struct nand_operation {scalar_t__ instrs; scalar_t__ ninstrs; } ;
struct nand_op_parser_pattern {int (* exec ) (struct nand_chip*,TYPE_1__*) ;} ;
struct TYPE_2__ {scalar_t__ instrs; scalar_t__ ninstrs; scalar_t__ last_instr_end_off; scalar_t__ first_instr_start_off; } ;
struct nand_op_parser_ctx {scalar_t__ instrs; scalar_t__ ninstrs; TYPE_1__ subop; } ;
struct nand_op_parser {unsigned int npatterns; struct nand_op_parser_pattern* patterns; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ nand_op_parser_cmp_ctx (struct nand_op_parser_ctx*,struct nand_op_parser_ctx*) ; 
 int /*<<< orphan*/  nand_op_parser_match_pat (struct nand_op_parser_pattern const*,struct nand_op_parser_ctx*) ; 
 int /*<<< orphan*/  nand_op_parser_trace (struct nand_op_parser_ctx*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int stub1 (struct nand_chip*,TYPE_1__*) ; 

int nand_op_parser_exec_op(struct nand_chip *chip,
			   const struct nand_op_parser *parser,
			   const struct nand_operation *op, bool check_only)
{
	struct nand_op_parser_ctx ctx = {
		.subop.instrs = op->instrs,
		.instrs = op->instrs,
		.ninstrs = op->ninstrs,
	};
	unsigned int i;

	while (ctx.subop.instrs < op->instrs + op->ninstrs) {
		const struct nand_op_parser_pattern *pattern;
		struct nand_op_parser_ctx best_ctx;
		int ret, best_pattern = -1;

		for (i = 0; i < parser->npatterns; i++) {
			struct nand_op_parser_ctx test_ctx = ctx;

			pattern = &parser->patterns[i];
			if (!nand_op_parser_match_pat(pattern, &test_ctx))
				continue;

			if (best_pattern >= 0 &&
			    nand_op_parser_cmp_ctx(&test_ctx, &best_ctx) <= 0)
				continue;

			best_pattern = i;
			best_ctx = test_ctx;
		}

		if (best_pattern < 0) {
			pr_debug("->exec_op() parser: pattern not found!\n");
			return -ENOTSUPP;
		}

		ctx = best_ctx;
		nand_op_parser_trace(&ctx);

		if (!check_only) {
			pattern = &parser->patterns[best_pattern];
			ret = pattern->exec(chip, &ctx.subop);
			if (ret)
				return ret;
		}

		/*
		 * Update the context structure by pointing to the start of the
		 * next subop.
		 */
		ctx.subop.instrs = ctx.subop.instrs + ctx.subop.ninstrs;
		if (ctx.subop.last_instr_end_off)
			ctx.subop.instrs -= 1;

		ctx.subop.first_instr_start_off = ctx.subop.last_instr_end_off;
	}

	return 0;
}