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
typedef  int u8 ;
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct nfp_prog {int dummy; } ;
struct bpf_insn {int dst_reg; int src_reg; } ;
struct nfp_insn_meta {int umin_src; int umax_src; struct bpf_insn insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_UNC ; 
 int EINVAL ; 
 int __shl_imm64 (struct nfp_prog*,int,int) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  emit_br_bset (struct nfp_prog*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_prog_confirm_current_offset (struct nfp_prog*,scalar_t__) ; 
 scalar_t__ nfp_prog_current_offset (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  shl_reg64_ge32 (struct nfp_prog*,int,int) ; 
 int /*<<< orphan*/  shl_reg64_lt32 (struct nfp_prog*,int,int) ; 
 int /*<<< orphan*/  shl_reg64_lt32_high (struct nfp_prog*,int,int) ; 
 int /*<<< orphan*/  shl_reg64_lt32_low (struct nfp_prog*,int,int) ; 

__attribute__((used)) static int shl_reg64(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	u64 umin, umax;
	u8 dst, src;

	dst = insn->dst_reg * 2;
	umin = meta->umin_src;
	umax = meta->umax_src;
	if (umin == umax)
		return __shl_imm64(nfp_prog, dst, umin);

	src = insn->src_reg * 2;
	if (umax < 32) {
		shl_reg64_lt32(nfp_prog, dst, src);
	} else if (umin >= 32) {
		shl_reg64_ge32(nfp_prog, dst, src);
	} else {
		/* Generate different instruction sequences depending on runtime
		 * value of shift amount.
		 */
		u16 label_ge32, label_end;

		label_ge32 = nfp_prog_current_offset(nfp_prog) + 7;
		emit_br_bset(nfp_prog, reg_a(src), 5, label_ge32, 0);

		shl_reg64_lt32_high(nfp_prog, dst, src);
		label_end = nfp_prog_current_offset(nfp_prog) + 6;
		emit_br(nfp_prog, BR_UNC, label_end, 2);
		/* shl_reg64_lt32_low packed in delay slot. */
		shl_reg64_lt32_low(nfp_prog, dst, src);

		if (!nfp_prog_confirm_current_offset(nfp_prog, label_ge32))
			return -EINVAL;
		shl_reg64_ge32(nfp_prog, dst, src);

		if (!nfp_prog_confirm_current_offset(nfp_prog, label_end))
			return -EINVAL;
	}

	return 0;
}