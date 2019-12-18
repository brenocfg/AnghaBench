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
struct rcar_gyroadc {scalar_t__ mode; scalar_t__ model; scalar_t__ regs; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ RCAR_GYROADC_1_25MS_LENGTH ; 
 scalar_t__ RCAR_GYROADC_CLOCK_LENGTH ; 
 scalar_t__ RCAR_GYROADC_INTENR ; 
 scalar_t__ RCAR_GYROADC_MODEL_R8A7792 ; 
 scalar_t__ RCAR_GYROADC_MODE_SELECT ; 
 scalar_t__ RCAR_GYROADC_MODE_SELECT_1_MB88101A ; 
 scalar_t__ RCAR_GYROADC_START_STOP ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long const,scalar_t__) ; 

__attribute__((used)) static void rcar_gyroadc_hw_init(struct rcar_gyroadc *priv)
{
	const unsigned long clk_mhz = clk_get_rate(priv->clk) / 1000000;
	const unsigned long clk_mul =
		(priv->mode == RCAR_GYROADC_MODE_SELECT_1_MB88101A) ? 10 : 5;
	unsigned long clk_len = clk_mhz * clk_mul;

	/*
	 * According to the R-Car Gen2 datasheet Rev. 1.01, Sept 08 2014,
	 * page 77-7, clock length must be even number. If it's odd number,
	 * add one.
	 */
	if (clk_len & 1)
		clk_len++;

	/* Stop the GyroADC. */
	writel(0, priv->regs + RCAR_GYROADC_START_STOP);

	/* Disable IRQ on V2H. */
	if (priv->model == RCAR_GYROADC_MODEL_R8A7792)
		writel(0, priv->regs + RCAR_GYROADC_INTENR);

	/* Set mode and timing. */
	writel(priv->mode, priv->regs + RCAR_GYROADC_MODE_SELECT);
	writel(clk_len, priv->regs + RCAR_GYROADC_CLOCK_LENGTH);
	writel(clk_mhz * 1250, priv->regs + RCAR_GYROADC_1_25MS_LENGTH);
}