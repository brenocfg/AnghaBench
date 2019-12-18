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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
typedef  int s32 ;
typedef  enum shf_sc { ____Placeholder_shf_sc } shf_sc ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 unsigned int RE_REG_LM_IDX_MAX ; 
 int SHF_SC_L_SHF ; 
 int SHF_SC_NONE ; 
 int SHF_SC_R_SHF ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int abs (unsigned int) ; 
 int /*<<< orphan*/  emit_ld_field (struct nfp_prog*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_b (unsigned int) ; 
 int /*<<< orphan*/  reg_lm (int,unsigned int) ; 
 int /*<<< orphan*/  reg_lm_inc (int) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wrp_lmem_store(struct nfp_prog *nfp_prog, u8 src, u8 src_byte, s32 off,
	       unsigned int size, bool first, bool new_gpr, bool last, bool lm3,
	       bool needs_inc)
{
	bool should_inc = needs_inc && new_gpr && !last;
	u32 idx, dst_byte;
	enum shf_sc sc;
	swreg reg;
	int shf;
	u8 mask;

	if (WARN_ON_ONCE(src_byte + size > 4 || off % 4 + size > 4))
		return -EOPNOTSUPP;

	idx = off / 4;

	/* Move the entire word */
	if (size == 4) {
		wrp_mov(nfp_prog,
			should_inc ? reg_lm_inc(3) : reg_lm(lm3 ? 3 : 0, idx),
			reg_b(src));
		return 0;
	}

	if (WARN_ON_ONCE(lm3 && idx > RE_REG_LM_IDX_MAX))
		return -EOPNOTSUPP;

	dst_byte = off % 4;

	mask = (1 << size) - 1;
	mask <<= dst_byte;

	if (WARN_ON_ONCE(mask > 0xf))
		return -EOPNOTSUPP;

	shf = abs(src_byte - dst_byte) * 8;
	if (src_byte == dst_byte) {
		sc = SHF_SC_NONE;
	} else if (src_byte < dst_byte) {
		shf = 32 - shf;
		sc = SHF_SC_L_SHF;
	} else {
		sc = SHF_SC_R_SHF;
	}

	/* ld_field can address fewer indexes, if offset too large do RMW.
	 * Because we RMV twice we waste 2 cycles on unaligned 8 byte writes.
	 */
	if (idx <= RE_REG_LM_IDX_MAX) {
		reg = reg_lm(lm3 ? 3 : 0, idx);
	} else {
		reg = imm_a(nfp_prog);
		/* Only first and last LMEM locations are going to need RMW,
		 * the middle location will be overwritten fully.
		 */
		if (first || last)
			wrp_mov(nfp_prog, reg, reg_lm(0, idx));
	}

	emit_ld_field(nfp_prog, reg, mask, reg_b(src), sc, shf);

	if (new_gpr || last) {
		if (idx > RE_REG_LM_IDX_MAX)
			wrp_mov(nfp_prog, reg_lm(0, idx), reg);
		if (should_inc)
			wrp_mov(nfp_prog, reg_none(), reg_lm_inc(3));
	}

	return 0;
}