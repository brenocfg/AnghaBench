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
struct cal_ctx {int /*<<< orphan*/  dev; int /*<<< orphan*/  csi2_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_CSI2_VC_IRQENABLE (int) ; 
 int /*<<< orphan*/  CAL_HL_IRQENABLE_CLR (int) ; 
 int /*<<< orphan*/  CAL_HL_IRQ_CLEAR ; 
 int /*<<< orphan*/  CAL_HL_IRQ_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_irqs(struct cal_ctx *ctx)
{
	/* Disable IRQ_WDMA_END 0/1 */
	reg_write_field(ctx->dev,
			CAL_HL_IRQENABLE_CLR(2),
			CAL_HL_IRQ_CLEAR,
			CAL_HL_IRQ_MASK(ctx->csi2_port));
	/* Disable IRQ_WDMA_START 0/1 */
	reg_write_field(ctx->dev,
			CAL_HL_IRQENABLE_CLR(3),
			CAL_HL_IRQ_CLEAR,
			CAL_HL_IRQ_MASK(ctx->csi2_port));
	/* Todo: Add VC_IRQ and CSI2_COMPLEXIO_IRQ handling */
	reg_write(ctx->dev, CAL_CSI2_VC_IRQENABLE(1), 0);
}