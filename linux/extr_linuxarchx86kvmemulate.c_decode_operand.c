#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* ea; void* seg; } ;
struct TYPE_4__ {TYPE_1__ mem; void* reg; } ;
struct operand {int bytes; int orig_val; int val; void* type; int count; int /*<<< orphan*/  valptr; TYPE_2__ addr; } ;
struct x86_emulate_ctxt {int d; int op_bytes; struct operand memop; void* _eip; void* seg_override; int /*<<< orphan*/  modrm_rm; struct operand* memopp; } ;

/* Variables and functions */
 int BitOp ; 
 int ByteOp ; 
 void* OP_IMM ; 
 void* OP_MEM ; 
 void* OP_NONE ; 
 void* OP_REG ; 
#define  OpAcc 157 
#define  OpAccHi 156 
#define  OpAccLo 155 
#define  OpCL 154 
#define  OpCS 153 
#define  OpDI 152 
#define  OpDS 151 
#define  OpDX 150 
#define  OpES 149 
#define  OpFS 148 
#define  OpGS 147 
#define  OpImm 146 
#define  OpImm64 145 
#define  OpImmByte 144 
#define  OpImmFAddr 143 
#define  OpImmU 142 
#define  OpImmU16 141 
#define  OpImmUByte 140 
#define  OpImplicit 139 
#define  OpMem 138 
#define  OpMem16 137 
#define  OpMem32 136 
#define  OpMem64 135 
#define  OpMem8 134 
#define  OpMemFAddr 133 
#define  OpOne 132 
#define  OpReg 131 
#define  OpSI 130 
#define  OpSS 129 
#define  OpXLat 128 
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  VCPU_REGS_RBX ; 
 int /*<<< orphan*/  VCPU_REGS_RCX ; 
 int /*<<< orphan*/  VCPU_REGS_RDI ; 
 int /*<<< orphan*/  VCPU_REGS_RDX ; 
 int /*<<< orphan*/  VCPU_REGS_RSI ; 
 int VCPU_SREG_CS ; 
 int VCPU_SREG_DS ; 
 void* VCPU_SREG_ES ; 
 int VCPU_SREG_FS ; 
 int VCPU_SREG_GS ; 
 int VCPU_SREG_SS ; 
 int X86EMUL_CONTINUE ; 
 void* address_mask (struct x86_emulate_ctxt*,int /*<<< orphan*/ ) ; 
 int decode_imm (struct x86_emulate_ctxt*,struct operand*,int,int) ; 
 void* decode_register (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  decode_register_operand (struct x86_emulate_ctxt*,struct operand*) ; 
 int /*<<< orphan*/  fetch_bit_operand (struct x86_emulate_ctxt*) ; 
 int /*<<< orphan*/  fetch_register_operand (struct operand*) ; 
 int imm_size (struct x86_emulate_ctxt*) ; 
 int /*<<< orphan*/  insn_fetch_arr (int /*<<< orphan*/ ,int,struct x86_emulate_ctxt*) ; 
 int reg_read (struct x86_emulate_ctxt*,int /*<<< orphan*/ ) ; 
 void* reg_rmw (struct x86_emulate_ctxt*,int /*<<< orphan*/ ) ; 
 void* register_address (struct x86_emulate_ctxt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_operand(struct x86_emulate_ctxt *ctxt, struct operand *op,
			  unsigned d)
{
	int rc = X86EMUL_CONTINUE;

	switch (d) {
	case OpReg:
		decode_register_operand(ctxt, op);
		break;
	case OpImmUByte:
		rc = decode_imm(ctxt, op, 1, false);
		break;
	case OpMem:
		ctxt->memop.bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
	mem_common:
		*op = ctxt->memop;
		ctxt->memopp = op;
		if (ctxt->d & BitOp)
			fetch_bit_operand(ctxt);
		op->orig_val = op->val;
		break;
	case OpMem64:
		ctxt->memop.bytes = (ctxt->op_bytes == 8) ? 16 : 8;
		goto mem_common;
	case OpAcc:
		op->type = OP_REG;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addr.reg = reg_rmw(ctxt, VCPU_REGS_RAX);
		fetch_register_operand(op);
		op->orig_val = op->val;
		break;
	case OpAccLo:
		op->type = OP_REG;
		op->bytes = (ctxt->d & ByteOp) ? 2 : ctxt->op_bytes;
		op->addr.reg = reg_rmw(ctxt, VCPU_REGS_RAX);
		fetch_register_operand(op);
		op->orig_val = op->val;
		break;
	case OpAccHi:
		if (ctxt->d & ByteOp) {
			op->type = OP_NONE;
			break;
		}
		op->type = OP_REG;
		op->bytes = ctxt->op_bytes;
		op->addr.reg = reg_rmw(ctxt, VCPU_REGS_RDX);
		fetch_register_operand(op);
		op->orig_val = op->val;
		break;
	case OpDI:
		op->type = OP_MEM;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addr.mem.ea =
			register_address(ctxt, VCPU_REGS_RDI);
		op->addr.mem.seg = VCPU_SREG_ES;
		op->val = 0;
		op->count = 1;
		break;
	case OpDX:
		op->type = OP_REG;
		op->bytes = 2;
		op->addr.reg = reg_rmw(ctxt, VCPU_REGS_RDX);
		fetch_register_operand(op);
		break;
	case OpCL:
		op->type = OP_IMM;
		op->bytes = 1;
		op->val = reg_read(ctxt, VCPU_REGS_RCX) & 0xff;
		break;
	case OpImmByte:
		rc = decode_imm(ctxt, op, 1, true);
		break;
	case OpOne:
		op->type = OP_IMM;
		op->bytes = 1;
		op->val = 1;
		break;
	case OpImm:
		rc = decode_imm(ctxt, op, imm_size(ctxt), true);
		break;
	case OpImm64:
		rc = decode_imm(ctxt, op, ctxt->op_bytes, true);
		break;
	case OpMem8:
		ctxt->memop.bytes = 1;
		if (ctxt->memop.type == OP_REG) {
			ctxt->memop.addr.reg = decode_register(ctxt,
					ctxt->modrm_rm, true);
			fetch_register_operand(&ctxt->memop);
		}
		goto mem_common;
	case OpMem16:
		ctxt->memop.bytes = 2;
		goto mem_common;
	case OpMem32:
		ctxt->memop.bytes = 4;
		goto mem_common;
	case OpImmU16:
		rc = decode_imm(ctxt, op, 2, false);
		break;
	case OpImmU:
		rc = decode_imm(ctxt, op, imm_size(ctxt), false);
		break;
	case OpSI:
		op->type = OP_MEM;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addr.mem.ea =
			register_address(ctxt, VCPU_REGS_RSI);
		op->addr.mem.seg = ctxt->seg_override;
		op->val = 0;
		op->count = 1;
		break;
	case OpXLat:
		op->type = OP_MEM;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addr.mem.ea =
			address_mask(ctxt,
				reg_read(ctxt, VCPU_REGS_RBX) +
				(reg_read(ctxt, VCPU_REGS_RAX) & 0xff));
		op->addr.mem.seg = ctxt->seg_override;
		op->val = 0;
		break;
	case OpImmFAddr:
		op->type = OP_IMM;
		op->addr.mem.ea = ctxt->_eip;
		op->bytes = ctxt->op_bytes + 2;
		insn_fetch_arr(op->valptr, op->bytes, ctxt);
		break;
	case OpMemFAddr:
		ctxt->memop.bytes = ctxt->op_bytes + 2;
		goto mem_common;
	case OpES:
		op->type = OP_IMM;
		op->val = VCPU_SREG_ES;
		break;
	case OpCS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_CS;
		break;
	case OpSS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_SS;
		break;
	case OpDS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_DS;
		break;
	case OpFS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_FS;
		break;
	case OpGS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_GS;
		break;
	case OpImplicit:
		/* Special instructions do their own operand decoding. */
	default:
		op->type = OP_NONE; /* Disable writeback. */
		break;
	}

done:
	return rc;
}