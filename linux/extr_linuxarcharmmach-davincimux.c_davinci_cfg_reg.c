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
struct mux_config {int mask; unsigned int mask_offset; unsigned int mode; scalar_t__ mux_reg; int /*<<< orphan*/ * name; } ;
struct davinci_soc_info {unsigned long const pinmux_pins_num; struct mux_config* pinmux_pins; int /*<<< orphan*/  pinmux_base; } ;
typedef  int /*<<< orphan*/  DEFINE_SPINLOCK ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SZ_4K ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 struct davinci_soc_info davinci_soc_info ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pinmux_base ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int davinci_cfg_reg(const unsigned long index)
{
	static DEFINE_SPINLOCK(mux_spin_lock);
	struct davinci_soc_info *soc_info = &davinci_soc_info;
	unsigned long flags;
	const struct mux_config *cfg;
	unsigned int reg_orig = 0, reg = 0;
	unsigned int mask, warn = 0;

	if (WARN_ON(!soc_info->pinmux_pins))
		return -ENODEV;

	if (!pinmux_base) {
		pinmux_base = ioremap(soc_info->pinmux_base, SZ_4K);
		if (WARN_ON(!pinmux_base))
			return -ENOMEM;
	}

	if (index >= soc_info->pinmux_pins_num) {
		pr_err("Invalid pin mux index: %lu (%lu)\n",
		       index, soc_info->pinmux_pins_num);
		dump_stack();
		return -ENODEV;
	}

	cfg = &soc_info->pinmux_pins[index];

	if (cfg->name == NULL) {
		pr_err("No entry for the specified index\n");
		return -ENODEV;
	}

	/* Update the mux register in question */
	if (cfg->mask) {
		unsigned	tmp1, tmp2;

		spin_lock_irqsave(&mux_spin_lock, flags);
		reg_orig = __raw_readl(pinmux_base + cfg->mux_reg);

		mask = (cfg->mask << cfg->mask_offset);
		tmp1 = reg_orig & mask;
		reg = reg_orig & ~mask;

		tmp2 = (cfg->mode << cfg->mask_offset);
		reg |= tmp2;

		if (tmp1 != tmp2)
			warn = 1;

		__raw_writel(reg, pinmux_base + cfg->mux_reg);
		spin_unlock_irqrestore(&mux_spin_lock, flags);
	}

	if (warn) {
#ifdef CONFIG_DAVINCI_MUX_WARNINGS
		pr_warn("initialized %s\n", cfg->name);
#endif
	}

#ifdef CONFIG_DAVINCI_MUX_DEBUG
	if (cfg->debug || warn) {
		pr_warn("Setting register %s\n", cfg->name);
		pr_warn("   %s (0x%08x) = 0x%08x -> 0x%08x\n",
			cfg->mux_reg_name, cfg->mux_reg, reg_orig, reg);
	}
#endif

	return 0;
}