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
typedef  int u32 ;
struct tegra_kbc {int repeat_cnt; int /*<<< orphan*/  irq; scalar_t__ mmio; scalar_t__ num_pressed_keys; int /*<<< orphan*/  cp_dly_jiffies; int /*<<< orphan*/  debounce_cnt; int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ KBC_CONTROL_0 ; 
 int KBC_CONTROL_FIFO_CNT_INT_EN ; 
 int KBC_CONTROL_KBC_EN ; 
 int KBC_DEBOUNCE_CNT_SHIFT (unsigned int) ; 
 int KBC_FIFO_TH_CNT_SHIFT (int) ; 
 scalar_t__ KBC_INIT_DLY_0 ; 
 scalar_t__ KBC_INT_0 ; 
 scalar_t__ KBC_KP_ENT0_0 ; 
 scalar_t__ KBC_KP_ENT1_0 ; 
 int /*<<< orphan*/  KBC_MAX_DEBOUNCE_CNT ; 
 scalar_t__ KBC_RPT_DLY_0 ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_kbc_config_pins (struct tegra_kbc*) ; 
 int /*<<< orphan*/  tegra_kbc_setup_wakekeys (struct tegra_kbc*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int tegra_kbc_start(struct tegra_kbc *kbc)
{
	unsigned int debounce_cnt;
	u32 val = 0;
	int ret;

	ret = clk_prepare_enable(kbc->clk);
	if (ret)
		return ret;

	/* Reset the KBC controller to clear all previous status.*/
	reset_control_assert(kbc->rst);
	udelay(100);
	reset_control_deassert(kbc->rst);
	udelay(100);

	tegra_kbc_config_pins(kbc);
	tegra_kbc_setup_wakekeys(kbc, false);

	writel(kbc->repeat_cnt, kbc->mmio + KBC_RPT_DLY_0);

	/* Keyboard debounce count is maximum of 12 bits. */
	debounce_cnt = min(kbc->debounce_cnt, KBC_MAX_DEBOUNCE_CNT);
	val = KBC_DEBOUNCE_CNT_SHIFT(debounce_cnt);
	val |= KBC_FIFO_TH_CNT_SHIFT(1); /* set fifo interrupt threshold to 1 */
	val |= KBC_CONTROL_FIFO_CNT_INT_EN;  /* interrupt on FIFO threshold */
	val |= KBC_CONTROL_KBC_EN;     /* enable */
	writel(val, kbc->mmio + KBC_CONTROL_0);

	/*
	 * Compute the delay(ns) from interrupt mode to continuous polling
	 * mode so the timer routine is scheduled appropriately.
	 */
	val = readl(kbc->mmio + KBC_INIT_DLY_0);
	kbc->cp_dly_jiffies = usecs_to_jiffies((val & 0xfffff) * 32);

	kbc->num_pressed_keys = 0;

	/*
	 * Atomically clear out any remaining entries in the key FIFO
	 * and enable keyboard interrupts.
	 */
	while (1) {
		val = readl(kbc->mmio + KBC_INT_0);
		val >>= 4;
		if (!val)
			break;

		val = readl(kbc->mmio + KBC_KP_ENT0_0);
		val = readl(kbc->mmio + KBC_KP_ENT1_0);
	}
	writel(0x7, kbc->mmio + KBC_INT_0);

	enable_irq(kbc->irq);

	return 0;
}