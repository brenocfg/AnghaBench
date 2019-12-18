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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CTX_SWAP ; 
 int /*<<< orphan*/  CMD_MODE_32b ; 
 int /*<<< orphan*/  CMD_TGT_WRITE8_SWAP ; 
 int /*<<< orphan*/  emit_cmd (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_xfer (int) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
data_st_host_order(struct nfp_prog *nfp_prog, u8 dst_gpr, swreg offset,
		   u64 imm, u8 size)
{
	wrp_immed(nfp_prog, reg_xfer(0), imm);
	if (size == 8)
		wrp_immed(nfp_prog, reg_xfer(1), imm >> 32);

	emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 0,
		 reg_a(dst_gpr), offset, size - 1, CMD_CTX_SWAP);

	return 0;
}