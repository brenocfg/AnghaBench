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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CTX_SWAP ; 
 int /*<<< orphan*/  CMD_MODE_32b ; 
 int /*<<< orphan*/  CMD_TGT_WRITE8_SWAP ; 
 int /*<<< orphan*/  emit_cmd (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_a (unsigned int) ; 
 int /*<<< orphan*/  reg_xfer (unsigned int) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
data_stx_host_order(struct nfp_prog *nfp_prog, u8 dst_gpr, swreg offset,
		    u8 src_gpr, u8 size)
{
	unsigned int i;

	for (i = 0; i * 4 < size; i++)
		wrp_mov(nfp_prog, reg_xfer(i), reg_a(src_gpr + i));

	emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 0,
		 reg_a(dst_gpr), offset, size - 1, CMD_CTX_SWAP);

	return 0;
}