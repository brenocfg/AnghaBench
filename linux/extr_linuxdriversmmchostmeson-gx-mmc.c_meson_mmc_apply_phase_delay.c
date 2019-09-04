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
typedef  unsigned int u32 ;
struct meson_mmc_phase {unsigned int phase_mask; int delay_mask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned int __ffs (unsigned int) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_mmc_apply_phase_delay(struct meson_mmc_phase *mmc,
					unsigned int phase,
					unsigned int delay)
{
	u32 val;

	val = readl(mmc->reg);
	val &= ~mmc->phase_mask;
	val |= phase << __ffs(mmc->phase_mask);

	if (mmc->delay_mask) {
		val &= ~mmc->delay_mask;
		val |= delay << __ffs(mmc->delay_mask);
	}

	writel(val, mmc->reg);
}