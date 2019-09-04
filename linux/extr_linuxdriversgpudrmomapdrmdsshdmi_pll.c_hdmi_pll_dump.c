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
struct seq_file {int dummy; } ;
struct hdmi_pll_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLLCTRL_CFG1 ; 
 int /*<<< orphan*/  PLLCTRL_CFG2 ; 
 int /*<<< orphan*/  PLLCTRL_CFG3 ; 
 int /*<<< orphan*/  PLLCTRL_CFG4 ; 
 int /*<<< orphan*/  PLLCTRL_PLL_CONTROL ; 
 int /*<<< orphan*/  PLLCTRL_PLL_GO ; 
 int /*<<< orphan*/  PLLCTRL_PLL_STATUS ; 
 int /*<<< orphan*/  PLLCTRL_SSC_CFG1 ; 
 int /*<<< orphan*/  PLLCTRL_SSC_CFG2 ; 
 int /*<<< orphan*/  hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 

void hdmi_pll_dump(struct hdmi_pll_data *pll, struct seq_file *s)
{
#define DUMPPLL(r) seq_printf(s, "%-35s %08x\n", #r,\
		hdmi_read_reg(pll->base, r))

	DUMPPLL(PLLCTRL_PLL_CONTROL);
	DUMPPLL(PLLCTRL_PLL_STATUS);
	DUMPPLL(PLLCTRL_PLL_GO);
	DUMPPLL(PLLCTRL_CFG1);
	DUMPPLL(PLLCTRL_CFG2);
	DUMPPLL(PLLCTRL_CFG3);
	DUMPPLL(PLLCTRL_SSC_CFG1);
	DUMPPLL(PLLCTRL_SSC_CFG2);
	DUMPPLL(PLLCTRL_CFG4);
}