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
typedef  int u8 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct TYPE_4__ {unsigned int off; int dst_reg; } ;
struct TYPE_3__ {unsigned int range_start; } ;
struct nfp_insn_meta {TYPE_2__ insn; TYPE_1__ pkt_cache; } ;

/* Variables and functions */
 unsigned int REG_WIDTH ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  reg_xfer (int) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_reg_subpart (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_zext (struct nfp_prog*,struct nfp_insn_meta*,int) ; 

__attribute__((used)) static int
mem_ldx_data_from_pktcache_aligned(struct nfp_prog *nfp_prog,
				   struct nfp_insn_meta *meta,
				   unsigned int size)
{
	swreg dst_lo, dst_hi, src_lo;
	u8 dst_gpr, idx;

	idx = (meta->insn.off - meta->pkt_cache.range_start) / REG_WIDTH;
	dst_gpr = meta->insn.dst_reg * 2;
	dst_hi = reg_both(dst_gpr + 1);
	dst_lo = reg_both(dst_gpr);
	src_lo = reg_xfer(idx);

	if (size < REG_WIDTH) {
		wrp_reg_subpart(nfp_prog, dst_lo, src_lo, size, 0);
		wrp_zext(nfp_prog, meta, dst_gpr);
	} else if (size == REG_WIDTH) {
		wrp_mov(nfp_prog, dst_lo, src_lo);
		wrp_zext(nfp_prog, meta, dst_gpr);
	} else {
		swreg src_hi = reg_xfer(idx + 1);

		wrp_mov(nfp_prog, dst_lo, src_lo);
		wrp_mov(nfp_prog, dst_hi, src_hi);
	}

	return 0;
}