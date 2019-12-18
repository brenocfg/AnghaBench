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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CTX_SWAP ; 
 int /*<<< orphan*/  CMD_MODE_32b ; 
 int /*<<< orphan*/  CMD_TGT_READ8 ; 
 int /*<<< orphan*/  SHF_OP_NONE ; 
 int /*<<< orphan*/  SHF_SC_R_SHF ; 
 int /*<<< orphan*/  emit_cmd (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  pptr_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_both (scalar_t__) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  reg_xfer (unsigned int) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_zext (struct nfp_prog*,struct nfp_insn_meta*,scalar_t__) ; 

__attribute__((used)) static int
data_ld(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta, swreg offset,
	u8 dst_gpr, int size)
{
	unsigned int i;
	u16 shift, sz;

	/* We load the value from the address indicated in @offset and then
	 * shift out the data we don't need.  Note: this is big endian!
	 */
	sz = max(size, 4);
	shift = size < 4 ? 4 - size : 0;

	emit_cmd(nfp_prog, CMD_TGT_READ8, CMD_MODE_32b, 0,
		 pptr_reg(nfp_prog), offset, sz - 1, CMD_CTX_SWAP);

	i = 0;
	if (shift)
		emit_shf(nfp_prog, reg_both(dst_gpr), reg_none(), SHF_OP_NONE,
			 reg_xfer(0), SHF_SC_R_SHF, shift * 8);
	else
		for (; i * 4 < size; i++)
			wrp_mov(nfp_prog, reg_both(dst_gpr + i), reg_xfer(i));

	if (i < 2)
		wrp_zext(nfp_prog, meta, dst_gpr);

	return 0;
}