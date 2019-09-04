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
struct dss_pll_hw {int /*<<< orphan*/  mX_max; } ;
struct dss_pll {struct dss_pll_hw* hw; } ;
typedef  scalar_t__ (* dss_hsdiv_calc_func ) (int,unsigned long,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned long,unsigned long) ; 
 unsigned long ULONG_MAX ; 
 int max (int /*<<< orphan*/ ,unsigned long) ; 
 int min (unsigned int,int /*<<< orphan*/ ) ; 

bool dss_pll_hsdiv_calc_a(const struct dss_pll *pll, unsigned long clkdco,
		unsigned long out_min, unsigned long out_max,
		dss_hsdiv_calc_func func, void *data)
{
	const struct dss_pll_hw *hw = pll->hw;
	int m, m_start, m_stop;
	unsigned long out;

	out_min = out_min ? out_min : 1;
	out_max = out_max ? out_max : ULONG_MAX;

	m_start = max(DIV_ROUND_UP(clkdco, out_max), 1ul);

	m_stop = min((unsigned)(clkdco / out_min), hw->mX_max);

	for (m = m_start; m <= m_stop; ++m) {
		out = clkdco / m;

		if (func(m, out, data))
			return true;
	}

	return false;
}