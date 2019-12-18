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
typedef  int u32 ;
struct isp_device {int dummy; } ;
struct isp_csi2_device {scalar_t__ frame_skip; int output; int /*<<< orphan*/  regs1; struct isp_device* isp; } ;
struct isp_csi2_ctx_cfg {unsigned int ctxnum; int /*<<< orphan*/  format_id; } ;

/* Variables and functions */
 int CSI2_OUTPUT_MEMORY ; 
 int /*<<< orphan*/  ISPCSI2_CTX_IRQSTATUS (unsigned int) ; 
 int ISPCSI2_CTX_IRQSTATUS_FE_IRQ ; 
 int /*<<< orphan*/  csi2_ctx_config (struct isp_device*,struct isp_csi2_device*,struct isp_csi2_ctx_cfg*) ; 
 int /*<<< orphan*/  csi2_ctx_enable (struct isp_device*,struct isp_csi2_device*,unsigned int,int) ; 
 int /*<<< orphan*/  csi2_ctx_map_format (struct isp_csi2_device*) ; 
 int /*<<< orphan*/  csi2_isr_buffer (struct isp_csi2_device*) ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi2_isr_ctx(struct isp_csi2_device *csi2,
			 struct isp_csi2_ctx_cfg *ctx)
{
	struct isp_device *isp = csi2->isp;
	unsigned int n = ctx->ctxnum;
	u32 status;

	status = isp_reg_readl(isp, csi2->regs1, ISPCSI2_CTX_IRQSTATUS(n));
	isp_reg_writel(isp, status, csi2->regs1, ISPCSI2_CTX_IRQSTATUS(n));

	if (!(status & ISPCSI2_CTX_IRQSTATUS_FE_IRQ))
		return;

	/* Skip interrupts until we reach the frame skip count. The CSI2 will be
	 * automatically disabled, as the frame skip count has been programmed
	 * in the CSI2_CTx_CTRL1::COUNT field, so re-enable it.
	 *
	 * It would have been nice to rely on the FRAME_NUMBER interrupt instead
	 * but it turned out that the interrupt is only generated when the CSI2
	 * writes to memory (the CSI2_CTx_CTRL1::COUNT field is decreased
	 * correctly and reaches 0 when data is forwarded to the video port only
	 * but no interrupt arrives). Maybe a CSI2 hardware bug.
	 */
	if (csi2->frame_skip) {
		csi2->frame_skip--;
		if (csi2->frame_skip == 0) {
			ctx->format_id = csi2_ctx_map_format(csi2);
			csi2_ctx_config(isp, csi2, ctx);
			csi2_ctx_enable(isp, csi2, n, 1);
		}
		return;
	}

	if (csi2->output & CSI2_OUTPUT_MEMORY)
		csi2_isr_buffer(csi2);
}