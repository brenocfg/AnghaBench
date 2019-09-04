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
typedef  int u8 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct TYPE_6__ {int off; int src_reg; int dst_reg; int /*<<< orphan*/  code; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct nfp_insn_meta {scalar_t__ ldst_gather_len; TYPE_3__ insn; TYPE_2__* paired_st; TYPE_1__ ptr; } ;
typedef  int s16 ;
struct TYPE_5__ {int off; int dst_reg; } ;

/* Variables and functions */
#define  BPF_B 131 
#define  BPF_DW 130 
#define  BPF_H 129 
 int BPF_SIZE (int /*<<< orphan*/ ) ; 
#define  BPF_W 128 
 int /*<<< orphan*/  CMD_CTX_SWAP ; 
 int /*<<< orphan*/  CMD_MODE_32b ; 
 int /*<<< orphan*/  CMD_MODE_40b_BA ; 
 int CMD_OVE_LEN ; 
 int /*<<< orphan*/  CMD_OV_LEN ; 
 int /*<<< orphan*/  CMD_TGT_READ32_SWAP ; 
 int /*<<< orphan*/  CMD_TGT_WRITE32_SWAP ; 
 int /*<<< orphan*/  CMD_TGT_WRITE8_SWAP ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_ALIGNED (int,int) ; 
 scalar_t__ PTR_TO_MAP_VALUE ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  addr40_offset (struct nfp_prog*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_cmd (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_cmd_any (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_cmd_indir (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  re_load_imm_any (struct nfp_prog*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  reg_xfer (int) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_reg_subpart (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int nfp_cpp_memcpy(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	bool descending_seq = meta->ldst_gather_len < 0;
	s16 len = abs(meta->ldst_gather_len);
	swreg src_base, off;
	bool src_40bit_addr;
	unsigned int i;
	u8 xfer_num;

	off = re_load_imm_any(nfp_prog, meta->insn.off, imm_b(nfp_prog));
	src_40bit_addr = meta->ptr.type == PTR_TO_MAP_VALUE;
	src_base = reg_a(meta->insn.src_reg * 2);
	xfer_num = round_up(len, 4) / 4;

	if (src_40bit_addr)
		addr40_offset(nfp_prog, meta->insn.src_reg * 2, off, &src_base,
			      &off);

	/* Setup PREV_ALU fields to override memory read length. */
	if (len > 32)
		wrp_immed(nfp_prog, reg_none(),
			  CMD_OVE_LEN | FIELD_PREP(CMD_OV_LEN, xfer_num - 1));

	/* Memory read from source addr into transfer-in registers. */
	emit_cmd_any(nfp_prog, CMD_TGT_READ32_SWAP,
		     src_40bit_addr ? CMD_MODE_40b_BA : CMD_MODE_32b, 0,
		     src_base, off, xfer_num - 1, CMD_CTX_SWAP, len > 32);

	/* Move from transfer-in to transfer-out. */
	for (i = 0; i < xfer_num; i++)
		wrp_mov(nfp_prog, reg_xfer(i), reg_xfer(i));

	off = re_load_imm_any(nfp_prog, meta->paired_st->off, imm_b(nfp_prog));

	if (len <= 8) {
		/* Use single direct_ref write8. */
		emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 0,
			 reg_a(meta->paired_st->dst_reg * 2), off, len - 1,
			 CMD_CTX_SWAP);
	} else if (len <= 32 && IS_ALIGNED(len, 4)) {
		/* Use single direct_ref write32. */
		emit_cmd(nfp_prog, CMD_TGT_WRITE32_SWAP, CMD_MODE_32b, 0,
			 reg_a(meta->paired_st->dst_reg * 2), off, xfer_num - 1,
			 CMD_CTX_SWAP);
	} else if (len <= 32) {
		/* Use single indirect_ref write8. */
		wrp_immed(nfp_prog, reg_none(),
			  CMD_OVE_LEN | FIELD_PREP(CMD_OV_LEN, len - 1));
		emit_cmd_indir(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 0,
			       reg_a(meta->paired_st->dst_reg * 2), off,
			       len - 1, CMD_CTX_SWAP);
	} else if (IS_ALIGNED(len, 4)) {
		/* Use single indirect_ref write32. */
		wrp_immed(nfp_prog, reg_none(),
			  CMD_OVE_LEN | FIELD_PREP(CMD_OV_LEN, xfer_num - 1));
		emit_cmd_indir(nfp_prog, CMD_TGT_WRITE32_SWAP, CMD_MODE_32b, 0,
			       reg_a(meta->paired_st->dst_reg * 2), off,
			       xfer_num - 1, CMD_CTX_SWAP);
	} else if (len <= 40) {
		/* Use one direct_ref write32 to write the first 32-bytes, then
		 * another direct_ref write8 to write the remaining bytes.
		 */
		emit_cmd(nfp_prog, CMD_TGT_WRITE32_SWAP, CMD_MODE_32b, 0,
			 reg_a(meta->paired_st->dst_reg * 2), off, 7,
			 CMD_CTX_SWAP);

		off = re_load_imm_any(nfp_prog, meta->paired_st->off + 32,
				      imm_b(nfp_prog));
		emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 8,
			 reg_a(meta->paired_st->dst_reg * 2), off, len - 33,
			 CMD_CTX_SWAP);
	} else {
		/* Use one indirect_ref write32 to write 4-bytes aligned length,
		 * then another direct_ref write8 to write the remaining bytes.
		 */
		u8 new_off;

		wrp_immed(nfp_prog, reg_none(),
			  CMD_OVE_LEN | FIELD_PREP(CMD_OV_LEN, xfer_num - 2));
		emit_cmd_indir(nfp_prog, CMD_TGT_WRITE32_SWAP, CMD_MODE_32b, 0,
			       reg_a(meta->paired_st->dst_reg * 2), off,
			       xfer_num - 2, CMD_CTX_SWAP);
		new_off = meta->paired_st->off + (xfer_num - 1) * 4;
		off = re_load_imm_any(nfp_prog, new_off, imm_b(nfp_prog));
		emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b,
			 xfer_num - 1, reg_a(meta->paired_st->dst_reg * 2), off,
			 (len & 0x3) - 1, CMD_CTX_SWAP);
	}

	/* TODO: The following extra load is to make sure data flow be identical
	 *  before and after we do memory copy optimization.
	 *
	 *  The load destination register is not guaranteed to be dead, so we
	 *  need to make sure it is loaded with the value the same as before
	 *  this transformation.
	 *
	 *  These extra loads could be removed once we have accurate register
	 *  usage information.
	 */
	if (descending_seq)
		xfer_num = 0;
	else if (BPF_SIZE(meta->insn.code) != BPF_DW)
		xfer_num = xfer_num - 1;
	else
		xfer_num = xfer_num - 2;

	switch (BPF_SIZE(meta->insn.code)) {
	case BPF_B:
		wrp_reg_subpart(nfp_prog, reg_both(meta->insn.dst_reg * 2),
				reg_xfer(xfer_num), 1,
				IS_ALIGNED(len, 4) ? 3 : (len & 3) - 1);
		break;
	case BPF_H:
		wrp_reg_subpart(nfp_prog, reg_both(meta->insn.dst_reg * 2),
				reg_xfer(xfer_num), 2, (len & 3) ^ 2);
		break;
	case BPF_W:
		wrp_mov(nfp_prog, reg_both(meta->insn.dst_reg * 2),
			reg_xfer(0));
		break;
	case BPF_DW:
		wrp_mov(nfp_prog, reg_both(meta->insn.dst_reg * 2),
			reg_xfer(xfer_num));
		wrp_mov(nfp_prog, reg_both(meta->insn.dst_reg * 2 + 1),
			reg_xfer(xfer_num + 1));
		break;
	}

	if (BPF_SIZE(meta->insn.code) != BPF_DW)
		wrp_immed(nfp_prog, reg_both(meta->insn.dst_reg * 2 + 1), 0);

	return 0;
}