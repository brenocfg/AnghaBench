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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MODE_32b ; 
 int data_ld_host_order (struct nfp_prog*,struct nfp_insn_meta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_a (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
data_ld_host_order_addr32(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
			  u8 src_gpr, swreg offset, u8 dst_gpr, u8 size)
{
	return data_ld_host_order(nfp_prog, meta, dst_gpr, reg_a(src_gpr),
				  offset, size, CMD_MODE_32b);
}