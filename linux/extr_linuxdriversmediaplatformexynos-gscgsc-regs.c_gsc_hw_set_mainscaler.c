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
struct gsc_scaler {int /*<<< orphan*/  main_vratio; int /*<<< orphan*/  main_hratio; } ;
struct gsc_dev {scalar_t__ regs; } ;
struct gsc_ctx {struct gsc_scaler scaler; struct gsc_dev* gsc_dev; } ;

/* Variables and functions */
 scalar_t__ GSC_MAIN_H_RATIO ; 
 int /*<<< orphan*/  GSC_MAIN_H_RATIO_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ GSC_MAIN_V_RATIO ; 
 int /*<<< orphan*/  GSC_MAIN_V_RATIO_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void gsc_hw_set_mainscaler(struct gsc_ctx *ctx)
{
	struct gsc_dev *dev = ctx->gsc_dev;
	struct gsc_scaler *sc = &ctx->scaler;
	u32 cfg;

	cfg = GSC_MAIN_H_RATIO_VALUE(sc->main_hratio);
	writel(cfg, dev->regs + GSC_MAIN_H_RATIO);

	cfg = GSC_MAIN_V_RATIO_VALUE(sc->main_vratio);
	writel(cfg, dev->regs + GSC_MAIN_V_RATIO);
}