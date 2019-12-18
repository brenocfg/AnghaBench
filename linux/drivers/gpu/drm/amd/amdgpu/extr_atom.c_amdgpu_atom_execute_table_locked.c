#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct atom_context {scalar_t__ cmd_table; } ;
struct TYPE_4__ {int ps_shift; int start; int abort; int /*<<< orphan*/ * ws; scalar_t__ last_jump; int /*<<< orphan*/ * ps; struct atom_context* ctx; } ;
typedef  TYPE_1__ atom_exec_context ;
struct TYPE_5__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (TYPE_1__*,int*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ATOM_CT_CODE_PTR ; 
 int ATOM_CT_PS_MASK ; 
 scalar_t__ ATOM_CT_PS_PTR ; 
 scalar_t__ ATOM_CT_SIZE_PTR ; 
 scalar_t__ ATOM_CT_WS_PTR ; 
 unsigned char ATOM_OP_CNT ; 
 unsigned char ATOM_OP_EOT ; 
 unsigned char ATOM_OP_NAMES_CNT ; 
 int CU16 (scalar_t__) ; 
 int CU8 (scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int,int,int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SDEBUG (char*,...) ; 
 int /*<<< orphan*/ * atom_op_names ; 
 int /*<<< orphan*/  debug_depth ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 TYPE_3__* opcode_table ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_atom_execute_table_locked(struct atom_context *ctx, int index, uint32_t * params)
{
	int base = CU16(ctx->cmd_table + 4 + 2 * index);
	int len, ws, ps, ptr;
	unsigned char op;
	atom_exec_context ectx;
	int ret = 0;

	if (!base)
		return -EINVAL;

	len = CU16(base + ATOM_CT_SIZE_PTR);
	ws = CU8(base + ATOM_CT_WS_PTR);
	ps = CU8(base + ATOM_CT_PS_PTR) & ATOM_CT_PS_MASK;
	ptr = base + ATOM_CT_CODE_PTR;

	SDEBUG(">> execute %04X (len %d, WS %d, PS %d)\n", base, len, ws, ps);

	ectx.ctx = ctx;
	ectx.ps_shift = ps / 4;
	ectx.start = base;
	ectx.ps = params;
	ectx.abort = false;
	ectx.last_jump = 0;
	if (ws)
		ectx.ws = kcalloc(4, ws, GFP_KERNEL);
	else
		ectx.ws = NULL;

	debug_depth++;
	while (1) {
		op = CU8(ptr++);
		if (op < ATOM_OP_NAMES_CNT)
			SDEBUG("%s @ 0x%04X\n", atom_op_names[op], ptr - 1);
		else
			SDEBUG("[%d] @ 0x%04X\n", op, ptr - 1);
		if (ectx.abort) {
			DRM_ERROR("atombios stuck executing %04X (len %d, WS %d, PS %d) @ 0x%04X\n",
				base, len, ws, ps, ptr - 1);
			ret = -EINVAL;
			goto free;
		}

		if (op < ATOM_OP_CNT && op > 0)
			opcode_table[op].func(&ectx, &ptr,
					      opcode_table[op].arg);
		else
			break;

		if (op == ATOM_OP_EOT)
			break;
	}
	debug_depth--;
	SDEBUG("<<\n");

free:
	if (ws)
		kfree(ectx.ws);
	return ret;
}