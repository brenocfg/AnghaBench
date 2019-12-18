#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int maxlen; } ;
struct TYPE_8__ {unsigned int maxcycles; } ;
struct TYPE_12__ {TYPE_5__ data; TYPE_2__ addr; } ;
struct nand_op_parser_pattern_elem {int type; TYPE_6__ ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; } ;
struct TYPE_7__ {int /*<<< orphan*/  naddrs; } ;
struct TYPE_10__ {TYPE_3__ data; TYPE_1__ addr; } ;
struct nand_op_instr {TYPE_4__ ctx; } ;

/* Variables and functions */
#define  NAND_OP_ADDR_INSTR 130 
#define  NAND_OP_DATA_IN_INSTR 129 
#define  NAND_OP_DATA_OUT_INSTR 128 

__attribute__((used)) static bool
nand_op_parser_must_split_instr(const struct nand_op_parser_pattern_elem *pat,
				const struct nand_op_instr *instr,
				unsigned int *start_offset)
{
	switch (pat->type) {
	case NAND_OP_ADDR_INSTR:
		if (!pat->ctx.addr.maxcycles)
			break;

		if (instr->ctx.addr.naddrs - *start_offset >
		    pat->ctx.addr.maxcycles) {
			*start_offset += pat->ctx.addr.maxcycles;
			return true;
		}
		break;

	case NAND_OP_DATA_IN_INSTR:
	case NAND_OP_DATA_OUT_INSTR:
		if (!pat->ctx.data.maxlen)
			break;

		if (instr->ctx.data.len - *start_offset >
		    pat->ctx.data.maxlen) {
			*start_offset += pat->ctx.data.maxlen;
			return true;
		}
		break;

	default:
		break;
	}

	return false;
}