#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vpe_ctx {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vpdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPE_INT0_ENABLE0_CLR ; 
 int /*<<< orphan*/  VPE_INT0_ENABLE1_CLR ; 
 int /*<<< orphan*/  vpdma_enable_list_complete_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void disable_irqs(struct vpe_ctx *ctx)
{
	write_reg(ctx->dev, VPE_INT0_ENABLE0_CLR, 0xffffffff);
	write_reg(ctx->dev, VPE_INT0_ENABLE1_CLR, 0xffffffff);

	vpdma_enable_list_complete_irq(ctx->dev->vpdma, 0, 0, false);
}