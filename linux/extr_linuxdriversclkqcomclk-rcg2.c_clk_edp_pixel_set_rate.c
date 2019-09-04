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
struct freq_tbl {int pre_div; int n; scalar_t__ m; } ;
struct frac_entry {int den; scalar_t__ num; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_rcg2 {scalar_t__ cmd_rcgr; TYPE_1__ clkr; int /*<<< orphan*/  hid_width; struct freq_tbl* freq_tbl; } ;
struct clk_hw {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CFG_REG ; 
 int CFG_SRC_DIV_SHIFT ; 
 int EINVAL ; 
 int clk_rcg2_configure (struct clk_rcg2*,struct freq_tbl*) ; 
 int div_s64 (int,scalar_t__) ; 
 struct frac_entry* frac_table_675m ; 
 struct frac_entry* frac_table_810m ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static int clk_edp_pixel_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	struct freq_tbl f = *rcg->freq_tbl;
	const struct frac_entry *frac;
	int delta = 100000;
	s64 src_rate = parent_rate;
	s64 request;
	u32 mask = BIT(rcg->hid_width) - 1;
	u32 hid_div;

	if (src_rate == 810000000)
		frac = frac_table_810m;
	else
		frac = frac_table_675m;

	for (; frac->num; frac++) {
		request = rate;
		request *= frac->den;
		request = div_s64(request, frac->num);
		if ((src_rate < (request - delta)) ||
		    (src_rate > (request + delta)))
			continue;

		regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG,
				&hid_div);
		f.pre_div = hid_div;
		f.pre_div >>= CFG_SRC_DIV_SHIFT;
		f.pre_div &= mask;
		f.m = frac->num;
		f.n = frac->den;

		return clk_rcg2_configure(rcg, &f);
	}

	return -EINVAL;
}