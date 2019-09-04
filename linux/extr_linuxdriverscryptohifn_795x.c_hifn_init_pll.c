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
typedef  unsigned int u32 ;
struct hifn_device {int pk_clk_freq; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int HIFN_1_PLL ; 
 unsigned int HIFN_PLL_BP ; 
 unsigned int HIFN_PLL_FCK_MAX ; 
 unsigned int HIFN_PLL_IS_1_8 ; 
 unsigned int HIFN_PLL_IS_9_12 ; 
 unsigned int HIFN_PLL_ND_SHIFT ; 
 unsigned int HIFN_PLL_PE_CLK_HBI ; 
 unsigned int HIFN_PLL_PE_CLK_PLL ; 
 unsigned int HIFN_PLL_PK_CLK_HBI ; 
 unsigned int HIFN_PLL_PK_CLK_PLL ; 
 unsigned int HIFN_PLL_REF_CLK_HBI ; 
 unsigned int HIFN_PLL_REF_CLK_PLL ; 
 unsigned int HIFN_PLL_RESERVED_1 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,char*) ; 
 char* hifn_pll_ref ; 
 int /*<<< orphan*/  hifn_write_1 (struct hifn_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned int simple_strtoul (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void hifn_init_pll(struct hifn_device *dev)
{
	unsigned int freq, m;
	u32 pllcfg;

	pllcfg = HIFN_1_PLL | HIFN_PLL_RESERVED_1;

	if (strncmp(hifn_pll_ref, "ext", 3) == 0)
		pllcfg |= HIFN_PLL_REF_CLK_PLL;
	else
		pllcfg |= HIFN_PLL_REF_CLK_HBI;

	if (hifn_pll_ref[3] != '\0')
		freq = simple_strtoul(hifn_pll_ref + 3, NULL, 10);
	else {
		freq = 66;
		dev_info(&dev->pdev->dev, "assuming %uMHz clock speed, override with hifn_pll_ref=%.3s<frequency>\n",
			 freq, hifn_pll_ref);
	}

	m = HIFN_PLL_FCK_MAX / freq;

	pllcfg |= (m / 2 - 1) << HIFN_PLL_ND_SHIFT;
	if (m <= 8)
		pllcfg |= HIFN_PLL_IS_1_8;
	else
		pllcfg |= HIFN_PLL_IS_9_12;

	/* Select clock source and enable clock bypass */
	hifn_write_1(dev, HIFN_1_PLL, pllcfg |
		     HIFN_PLL_PK_CLK_HBI | HIFN_PLL_PE_CLK_HBI | HIFN_PLL_BP);

	/* Let the chip lock to the input clock */
	mdelay(10);

	/* Disable clock bypass */
	hifn_write_1(dev, HIFN_1_PLL, pllcfg |
		     HIFN_PLL_PK_CLK_HBI | HIFN_PLL_PE_CLK_HBI);

	/* Switch the engines to the PLL */
	hifn_write_1(dev, HIFN_1_PLL, pllcfg |
		     HIFN_PLL_PK_CLK_PLL | HIFN_PLL_PE_CLK_PLL);

	/*
	 * The Fpk_clk runs at half the total speed. Its frequency is needed to
	 * calculate the minimum time between two reads of the rng. Since 33MHz
	 * is actually 33.333... we overestimate the frequency here, resulting
	 * in slightly larger intervals.
	 */
	dev->pk_clk_freq = 1000000 * (freq + 1) * m / 2;
}