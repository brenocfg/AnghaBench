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
typedef  void* u32 ;
struct isp_device {int dummy; } ;
struct isp_csi2_device {int /*<<< orphan*/  regs1; struct isp_csi2_ctx_cfg* contexts; struct isp_device* isp; } ;
struct isp_csi2_ctx_cfg {int /*<<< orphan*/  ctxnum; void* pong_addr; void* ping_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCSI2_CTX_DAT_PING_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISPCSI2_CTX_DAT_PONG_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi2_set_outaddr(struct isp_csi2_device *csi2, u32 addr)
{
	struct isp_device *isp = csi2->isp;
	struct isp_csi2_ctx_cfg *ctx = &csi2->contexts[0];

	ctx->ping_addr = addr;
	ctx->pong_addr = addr;
	isp_reg_writel(isp, ctx->ping_addr,
		       csi2->regs1, ISPCSI2_CTX_DAT_PING_ADDR(ctx->ctxnum));
	isp_reg_writel(isp, ctx->pong_addr,
		       csi2->regs1, ISPCSI2_CTX_DAT_PONG_ADDR(ctx->ctxnum));
}