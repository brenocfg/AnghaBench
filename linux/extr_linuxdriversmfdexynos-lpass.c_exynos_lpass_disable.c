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
struct exynos_lpass {int /*<<< orphan*/  sfr0_clk; int /*<<< orphan*/  top; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFR_LPASS_INTR_CA5_MASK ; 
 int /*<<< orphan*/  SFR_LPASS_INTR_CPU_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_lpass_disable(struct exynos_lpass *lpass)
{
	/* Mask any unmasked IP interrupt sources */
	regmap_write(lpass->top, SFR_LPASS_INTR_CPU_MASK, 0);
	regmap_write(lpass->top, SFR_LPASS_INTR_CA5_MASK, 0);

	clk_disable_unprepare(lpass->sfr0_clk);
}