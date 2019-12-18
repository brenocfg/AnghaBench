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
struct i740fb_par {int video_clk2_m; int video_clk2_n; int video_clk2_mn_msbs; int video_clk2_div_sel; } ;

/* Variables and functions */
 int I740_FFIX ; 
 int I740_MAX_VCO_FREQ ; 
 int I740_REF_FREQ ; 
 int I740_RFREQ ; 
 int I740_RFREQ_FIX ; 
 int REF_DIV_1 ; 
 int TARGET_MAX_N ; 
 int VCO_M_MSBS ; 
 int VCO_N_MSBS ; 
 int const abs (int) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i740_calc_vclk(u32 freq, struct i740fb_par *par)
{
	const u32 err_max    = freq / (200  * I740_RFREQ / I740_FFIX);
	const u32 err_target = freq / (1000 * I740_RFREQ / I740_FFIX);
	u32 err_best = 512 * I740_FFIX;
	u32 f_err, f_vco;
	int m_best = 0, n_best = 0, p_best = 0;
	int m, n;

	p_best = min(15, ilog2(I740_MAX_VCO_FREQ / (freq / I740_RFREQ_FIX)));
	f_vco = (freq * (1 << p_best)) / I740_RFREQ_FIX;
	freq = freq / I740_RFREQ_FIX;

	n = 2;
	do {
		n++;
		m = ((f_vco * n) / I740_REF_FREQ + 2) / 4;

		if (m < 3)
			m = 3;

		{
			u32 f_out = (((m * I740_REF_FREQ * 4)
				 / n) + ((1 << p_best) / 2)) / (1 << p_best);

			f_err = (freq - f_out);

			if (abs(f_err) < err_max) {
				m_best = m;
				n_best = n;
				err_best = f_err;
			}
		}
	} while ((abs(f_err) >= err_target) &&
		 ((n <= TARGET_MAX_N) || (abs(err_best) > err_max)));

	if (abs(f_err) < err_target) {
		m_best = m;
		n_best = n;
	}

	par->video_clk2_m = (m_best - 2) & 0xFF;
	par->video_clk2_n = (n_best - 2) & 0xFF;
	par->video_clk2_mn_msbs = ((((n_best - 2) >> 4) & VCO_N_MSBS)
				 | (((m_best - 2) >> 8) & VCO_M_MSBS));
	par->video_clk2_div_sel = ((p_best << 4) | REF_DIV_1);
}