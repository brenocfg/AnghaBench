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
struct clk_hw {int dummy; } ;
struct clk_gemini_pci {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEMINI_GLOBAL_CLOCK_CONTROL ; 
 unsigned int PCI_CLKRUN_EN ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_gemini_pci* to_pciclk (struct clk_hw*) ; 

__attribute__((used)) static int gemini_pci_is_enabled(struct clk_hw *hw)
{
	struct clk_gemini_pci *pciclk = to_pciclk(hw);
	unsigned int val;

	regmap_read(pciclk->map, GEMINI_GLOBAL_CLOCK_CONTROL, &val);
	return !!(val & PCI_CLKRUN_EN);
}