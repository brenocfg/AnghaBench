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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; int /*<<< orphan*/  hw; } ;
struct clk_pll {int /*<<< orphan*/  status_bit; int /*<<< orphan*/  status_reg; TYPE_1__ clkr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WARN (int,char*,char const*) ; 
 char* clk_hw_get_name (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_for_pll(struct clk_pll *pll)
{
	u32 val;
	int count;
	int ret;
	const char *name = clk_hw_get_name(&pll->clkr.hw);

	/* Wait for pll to enable. */
	for (count = 200; count > 0; count--) {
		ret = regmap_read(pll->clkr.regmap, pll->status_reg, &val);
		if (ret)
			return ret;
		if (val & BIT(pll->status_bit))
			return 0;
		udelay(1);
	}

	WARN(1, "%s didn't enable after voting for it!\n", name);
	return -ETIMEDOUT;
}