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
typedef  unsigned int u8 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct TYPE_4__ {unsigned int off; int dst_reg; } ;
struct TYPE_3__ {unsigned int range_start; } ;
struct nfp_insn_meta {TYPE_2__ insn; TYPE_1__ pkt_cache; } ;
typedef  unsigned int s16 ;

/* Variables and functions */
 unsigned int REG_WIDTH ; 
 int /*<<< orphan*/  reg_both (unsigned int) ; 
 int /*<<< orphan*/  reg_xfer (unsigned int) ; 
 int /*<<< orphan*/  wrp_reg_or_subpart (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wrp_reg_subpart (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wrp_zext (struct nfp_prog*,struct nfp_insn_meta*,unsigned int) ; 

__attribute__((used)) static int
mem_ldx_data_from_pktcache_unaligned(struct nfp_prog *nfp_prog,
				     struct nfp_insn_meta *meta,
				     unsigned int size)
{
	s16 range_start = meta->pkt_cache.range_start;
	s16 insn_off = meta->insn.off - range_start;
	swreg dst_lo, dst_hi, src_lo, src_mid;
	u8 dst_gpr = meta->insn.dst_reg * 2;
	u8 len_lo = size, len_mid = 0;
	u8 idx = insn_off / REG_WIDTH;
	u8 off = insn_off % REG_WIDTH;

	dst_hi = reg_both(dst_gpr + 1);
	dst_lo = reg_both(dst_gpr);
	src_lo = reg_xfer(idx);

	/* The read length could involve as many as three registers. */
	if (size > REG_WIDTH - off) {
		/* Calculate the part in the second register. */
		len_lo = REG_WIDTH - off;
		len_mid = size - len_lo;

		/* Calculate the part in the third register. */
		if (size > 2 * REG_WIDTH - off)
			len_mid = REG_WIDTH;
	}

	wrp_reg_subpart(nfp_prog, dst_lo, src_lo, len_lo, off);

	if (!len_mid) {
		wrp_zext(nfp_prog, meta, dst_gpr);
		return 0;
	}

	src_mid = reg_xfer(idx + 1);

	if (size <= REG_WIDTH) {
		wrp_reg_or_subpart(nfp_prog, dst_lo, src_mid, len_mid, len_lo);
		wrp_zext(nfp_prog, meta, dst_gpr);
	} else {
		swreg src_hi = reg_xfer(idx + 2);

		wrp_reg_or_subpart(nfp_prog, dst_lo, src_mid,
				   REG_WIDTH - len_lo, len_lo);
		wrp_reg_subpart(nfp_prog, dst_hi, src_mid, len_lo,
				REG_WIDTH - len_lo);
		wrp_reg_or_subpart(nfp_prog, dst_hi, src_hi, REG_WIDTH - len_lo,
				   len_lo);
	}

	return 0;
}