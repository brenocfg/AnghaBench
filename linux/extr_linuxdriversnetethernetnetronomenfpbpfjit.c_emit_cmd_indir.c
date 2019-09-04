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
typedef  enum cmd_tgt_map { ____Placeholder_cmd_tgt_map } cmd_tgt_map ;
typedef  enum cmd_ctx_swap { ____Placeholder_cmd_ctx_swap } cmd_ctx_swap ;

/* Variables and functions */
 int /*<<< orphan*/  emit_cmd_any (struct nfp_prog*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
emit_cmd_indir(struct nfp_prog *nfp_prog, enum cmd_tgt_map op, u8 mode, u8 xfer,
	       swreg lreg, swreg rreg, u8 size, enum cmd_ctx_swap ctx)
{
	emit_cmd_any(nfp_prog, op, mode, xfer, lreg, rreg, size, ctx, true);
}