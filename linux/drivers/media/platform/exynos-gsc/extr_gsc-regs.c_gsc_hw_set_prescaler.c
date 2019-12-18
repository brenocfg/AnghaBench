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
struct gsc_scaler {int /*<<< orphan*/  pre_vratio; int /*<<< orphan*/  pre_hratio; int /*<<< orphan*/  pre_shfactor; } ;
struct gsc_dev {scalar_t__ regs; } ;
struct gsc_ctx {struct gsc_scaler scaler; struct gsc_dev* gsc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSC_PRESC_H_RATIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_PRESC_SHFACTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_PRESC_V_RATIO (int /*<<< orphan*/ ) ; 
 scalar_t__ GSC_PRE_SCALE_RATIO ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void gsc_hw_set_prescaler(struct gsc_ctx *ctx)
{
	struct gsc_dev *dev = ctx->gsc_dev;
	struct gsc_scaler *sc = &ctx->scaler;
	u32 cfg;

	cfg = GSC_PRESC_SHFACTOR(sc->pre_shfactor);
	cfg |= GSC_PRESC_H_RATIO(sc->pre_hratio);
	cfg |= GSC_PRESC_V_RATIO(sc->pre_vratio);
	writel(cfg, dev->regs + GSC_PRE_SCALE_RATIO);
}