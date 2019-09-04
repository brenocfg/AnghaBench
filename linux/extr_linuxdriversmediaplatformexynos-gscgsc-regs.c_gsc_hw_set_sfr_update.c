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
struct gsc_dev {scalar_t__ regs; } ;
struct gsc_ctx {struct gsc_dev* gsc_dev; } ;

/* Variables and functions */
 scalar_t__ GSC_ENABLE ; 
 int /*<<< orphan*/  GSC_ENABLE_SFR_UPDATE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void gsc_hw_set_sfr_update(struct gsc_ctx *ctx)
{
	struct gsc_dev *dev = ctx->gsc_dev;
	u32 cfg;

	cfg = readl(dev->regs + GSC_ENABLE);
	cfg |= GSC_ENABLE_SFR_UPDATE;
	writel(cfg, dev->regs + GSC_ENABLE);
}