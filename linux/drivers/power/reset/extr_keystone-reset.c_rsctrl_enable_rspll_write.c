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

/* Variables and functions */
 int /*<<< orphan*/  RSCTRL_KEY ; 
 int /*<<< orphan*/  RSCTRL_KEY_MASK ; 
 scalar_t__ RSCTRL_RG ; 
 int /*<<< orphan*/  pllctrl_regs ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rspll_offset ; 

__attribute__((used)) static inline int rsctrl_enable_rspll_write(void)
{
	return regmap_update_bits(pllctrl_regs, rspll_offset + RSCTRL_RG,
				  RSCTRL_KEY_MASK, RSCTRL_KEY);
}