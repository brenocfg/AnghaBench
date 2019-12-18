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
struct TYPE_2__ {int /*<<< orphan*/  var; } ;
struct sa1100fb_info {int* palette_cpu; int reg_lccr3; int reg_lccr2; int reg_lccr1; int reg_lccr0; int dbar1; int dbar2; scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; TYPE_1__ fb; } ;

/* Variables and functions */
 scalar_t__ DBAR1 ; 
 scalar_t__ DBAR2 ; 
 scalar_t__ LCCR0 ; 
 int LCCR0_LEN ; 
 scalar_t__ LCCR1 ; 
 scalar_t__ LCCR2 ; 
 scalar_t__ LCCR3 ; 
 int /*<<< orphan*/  SHANNON_GPIO_DISP_EN ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ machine_is_shannon () ; 
 int palette_pbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sa1100fb_enable_controller(struct sa1100fb_info *fbi)
{
	dev_dbg(fbi->dev, "Enabling LCD controller\n");

	/*
	 * Make sure the mode bits are present in the first palette entry
	 */
	fbi->palette_cpu[0] &= 0xcfff;
	fbi->palette_cpu[0] |= palette_pbs(&fbi->fb.var);

	/* enable LCD controller clock */
	clk_prepare_enable(fbi->clk);

	/* Sequence from 11.7.10 */
	writel_relaxed(fbi->reg_lccr3, fbi->base + LCCR3);
	writel_relaxed(fbi->reg_lccr2, fbi->base + LCCR2);
	writel_relaxed(fbi->reg_lccr1, fbi->base + LCCR1);
	writel_relaxed(fbi->reg_lccr0 & ~LCCR0_LEN, fbi->base + LCCR0);
	writel_relaxed(fbi->dbar1, fbi->base + DBAR1);
	writel_relaxed(fbi->dbar2, fbi->base + DBAR2);
	writel_relaxed(fbi->reg_lccr0 | LCCR0_LEN, fbi->base + LCCR0);

	if (machine_is_shannon())
		gpio_set_value(SHANNON_GPIO_DISP_EN, 1);

	dev_dbg(fbi->dev, "DBAR1: 0x%08x\n", readl_relaxed(fbi->base + DBAR1));
	dev_dbg(fbi->dev, "DBAR2: 0x%08x\n", readl_relaxed(fbi->base + DBAR2));
	dev_dbg(fbi->dev, "LCCR0: 0x%08x\n", readl_relaxed(fbi->base + LCCR0));
	dev_dbg(fbi->dev, "LCCR1: 0x%08x\n", readl_relaxed(fbi->base + LCCR1));
	dev_dbg(fbi->dev, "LCCR2: 0x%08x\n", readl_relaxed(fbi->base + LCCR2));
	dev_dbg(fbi->dev, "LCCR3: 0x%08x\n", readl_relaxed(fbi->base + LCCR3));
}