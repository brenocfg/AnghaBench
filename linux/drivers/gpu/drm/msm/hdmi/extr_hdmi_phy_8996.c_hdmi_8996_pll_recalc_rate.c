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
typedef  unsigned long u64 ;
typedef  int u32 ;
struct hdmi_pll_8996 {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_LOCK_CMP1_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_LOCK_CMP2_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_LOCK_CMP3_MODE0 ; 
 int /*<<< orphan*/  do_div (unsigned long,int) ; 
 int hdmi_pll_read (struct hdmi_pll_8996*,int /*<<< orphan*/ ) ; 
 struct hdmi_pll_8996* hw_clk_to_pll (struct clk_hw*) ; 
 unsigned long pll_cmp_to_fdata (int,unsigned long) ; 

__attribute__((used)) static unsigned long hdmi_8996_pll_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct hdmi_pll_8996 *pll = hw_clk_to_pll(hw);
	u64 fdata;
	u32 cmp1, cmp2, cmp3, pll_cmp;

	cmp1 = hdmi_pll_read(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP1_MODE0);
	cmp2 = hdmi_pll_read(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP2_MODE0);
	cmp3 = hdmi_pll_read(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP3_MODE0);

	pll_cmp = cmp1 | (cmp2 << 8) | (cmp3 << 16);

	fdata = pll_cmp_to_fdata(pll_cmp + 1, parent_rate);

	do_div(fdata, 10);

	return fdata;
}