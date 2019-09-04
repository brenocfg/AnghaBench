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
struct rcar_gyroadc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ RCAR_GYROADC_START_STOP ; 
 int /*<<< orphan*/  RCAR_GYROADC_START_STOP_START ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rcar_gyroadc_hw_start(struct rcar_gyroadc *priv)
{
	/* Start sampling. */
	writel(RCAR_GYROADC_START_STOP_START,
	       priv->regs + RCAR_GYROADC_START_STOP);

	/*
	 * Wait for the first conversion to complete. This is longer than
	 * the 1.25 mS in the datasheet because 1.25 mS is not enough for
	 * the hardware to deliver the first sample and the hardware does
	 * then return zeroes instead of valid data.
	 */
	mdelay(3);
}