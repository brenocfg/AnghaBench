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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int dummy; } ;
typedef  enum cmd_mode { ____Placeholder_cmd_mode } cmd_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CTX_SWAP ; 
 int /*<<< orphan*/  CMD_TGT_READ32_SWAP ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHF_SC_NONE ; 
 int /*<<< orphan*/  emit_cmd (struct nfp_prog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_ld_field_any (struct nfp_prog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  reg_xfer (unsigned int) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_zext (struct nfp_prog*,struct nfp_insn_meta*,int) ; 

__attribute__((used)) static int
data_ld_host_order(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
		   u8 dst_gpr, swreg lreg, swreg rreg, int size,
		   enum cmd_mode mode)
{
	unsigned int i;
	u8 mask, sz;

	/* We load the value from the address indicated in rreg + lreg and then
	 * mask out the data we don't need.  Note: this is little endian!
	 */
	sz = max(size, 4);
	mask = size < 4 ? GENMASK(size - 1, 0) : 0;

	emit_cmd(nfp_prog, CMD_TGT_READ32_SWAP, mode, 0,
		 lreg, rreg, sz / 4 - 1, CMD_CTX_SWAP);

	i = 0;
	if (mask)
		emit_ld_field_any(nfp_prog, reg_both(dst_gpr), mask,
				  reg_xfer(0), SHF_SC_NONE, 0, true);
	else
		for (; i * 4 < size; i++)
			wrp_mov(nfp_prog, reg_both(dst_gpr + i), reg_xfer(i));

	if (i < 2)
		wrp_zext(nfp_prog, meta, dst_gpr);

	return 0;
}