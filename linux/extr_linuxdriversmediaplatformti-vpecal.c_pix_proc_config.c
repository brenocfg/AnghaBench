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
typedef  int /*<<< orphan*/  u32 ;
struct cal_ctx {int /*<<< orphan*/  csi2_port; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_GEN_ENABLE ; 
 int /*<<< orphan*/  CAL_PIX_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAL_PIX_PROC_CPORT_MASK ; 
 int /*<<< orphan*/  CAL_PIX_PROC_DPCMD_BYPASS ; 
 int /*<<< orphan*/  CAL_PIX_PROC_DPCMD_MASK ; 
 int /*<<< orphan*/  CAL_PIX_PROC_DPCME_BYPASS ; 
 int /*<<< orphan*/  CAL_PIX_PROC_DPCME_MASK ; 
 int /*<<< orphan*/  CAL_PIX_PROC_EN_MASK ; 
 int /*<<< orphan*/  CAL_PIX_PROC_EXTRACT_B8 ; 
 int /*<<< orphan*/  CAL_PIX_PROC_EXTRACT_MASK ; 
 int /*<<< orphan*/  CAL_PIX_PROC_PACK_B8 ; 
 int /*<<< orphan*/  CAL_PIX_PROC_PACK_MASK ; 
 int /*<<< orphan*/  ctx_dbg (int,struct cal_ctx*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pix_proc_config(struct cal_ctx *ctx)
{
	u32 val;

	val = reg_read(ctx->dev, CAL_PIX_PROC(ctx->csi2_port));
	set_field(&val, CAL_PIX_PROC_EXTRACT_B8, CAL_PIX_PROC_EXTRACT_MASK);
	set_field(&val, CAL_PIX_PROC_DPCMD_BYPASS, CAL_PIX_PROC_DPCMD_MASK);
	set_field(&val, CAL_PIX_PROC_DPCME_BYPASS, CAL_PIX_PROC_DPCME_MASK);
	set_field(&val, CAL_PIX_PROC_PACK_B8, CAL_PIX_PROC_PACK_MASK);
	set_field(&val, ctx->csi2_port, CAL_PIX_PROC_CPORT_MASK);
	set_field(&val, CAL_GEN_ENABLE, CAL_PIX_PROC_EN_MASK);
	reg_write(ctx->dev, CAL_PIX_PROC(ctx->csi2_port), val);
	ctx_dbg(3, ctx, "CAL_PIX_PROC(%d) = 0x%08x\n", ctx->csi2_port,
		reg_read(ctx->dev, CAL_PIX_PROC(ctx->csi2_port)));
}