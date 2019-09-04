#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
typedef  size_t u32 ;
struct mipi_phy_params {int hstx_ckg_sel; size_t pll_fbd_p; int pll_pre_div1p; int pll_fbd_2p; size_t pll_pre_p; size_t pll_fbd_s; int pll_fbd_div1f; int pll_fbd_div5f; int /*<<< orphan*/  pll_vco_750M; } ;
struct TYPE_3__ {size_t min_range_kHz; size_t max_range_kHz; int hstx_ckg_sel; int /*<<< orphan*/  pll_vco_750M; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,size_t) ; 
 size_t PHY_REF_CLK_PERIOD_PS ; 
 TYPE_1__* dphy_range_info ; 

__attribute__((used)) static u32 dsi_calc_phy_rate(u32 req_kHz, struct mipi_phy_params *phy)
{
	u32 ref_clk_ps = PHY_REF_CLK_PERIOD_PS;
	u32 tmp_kHz = req_kHz;
	u32 i = 0;
	u32 q_pll = 1;
	u32 m_pll = 0;
	u32 n_pll = 0;
	u32 r_pll = 1;
	u32 m_n = 0;
	u32 m_n_int = 0;
	u32 f_kHz = 0;
	u64 temp;

	/*
	 * Find a rate >= req_kHz.
	 */
	do {
		f_kHz = tmp_kHz;

		for (i = 0; i < ARRAY_SIZE(dphy_range_info); i++)
			if (f_kHz >= dphy_range_info[i].min_range_kHz &&
			    f_kHz <= dphy_range_info[i].max_range_kHz)
				break;

		if (i == ARRAY_SIZE(dphy_range_info)) {
			DRM_ERROR("%dkHz out of range\n", f_kHz);
			return 0;
		}

		phy->pll_vco_750M = dphy_range_info[i].pll_vco_750M;
		phy->hstx_ckg_sel = dphy_range_info[i].hstx_ckg_sel;

		if (phy->hstx_ckg_sel <= 7 &&
		    phy->hstx_ckg_sel >= 4)
			q_pll = 0x10 >> (7 - phy->hstx_ckg_sel);

		temp = f_kHz * (u64)q_pll * (u64)ref_clk_ps;
		m_n_int = temp / (u64)1000000000;
		m_n = (temp % (u64)1000000000) / (u64)100000000;

		if (m_n_int % 2 == 0) {
			if (m_n * 6 >= 50) {
				n_pll = 2;
				m_pll = (m_n_int + 1) * n_pll;
			} else if (m_n * 6 >= 30) {
				n_pll = 3;
				m_pll = m_n_int * n_pll + 2;
			} else {
				n_pll = 1;
				m_pll = m_n_int * n_pll;
			}
		} else {
			if (m_n * 6 >= 50) {
				n_pll = 1;
				m_pll = (m_n_int + 1) * n_pll;
			} else if (m_n * 6 >= 30) {
				n_pll = 1;
				m_pll = (m_n_int + 1) * n_pll;
			} else if (m_n * 6 >= 10) {
				n_pll = 3;
				m_pll = m_n_int * n_pll + 1;
			} else {
				n_pll = 2;
				m_pll = m_n_int * n_pll;
			}
		}

		if (n_pll == 1) {
			phy->pll_fbd_p = 0;
			phy->pll_pre_div1p = 1;
		} else {
			phy->pll_fbd_p = n_pll;
			phy->pll_pre_div1p = 0;
		}

		if (phy->pll_fbd_2p <= 7 && phy->pll_fbd_2p >= 4)
			r_pll = 0x10 >> (7 - phy->pll_fbd_2p);

		if (m_pll == 2) {
			phy->pll_pre_p = 0;
			phy->pll_fbd_s = 0;
			phy->pll_fbd_div1f = 0;
			phy->pll_fbd_div5f = 1;
		} else if (m_pll >= 2 * 2 * r_pll && m_pll <= 2 * 4 * r_pll) {
			phy->pll_pre_p = m_pll / (2 * r_pll);
			phy->pll_fbd_s = 0;
			phy->pll_fbd_div1f = 1;
			phy->pll_fbd_div5f = 0;
		} else if (m_pll >= 2 * 5 * r_pll && m_pll <= 2 * 150 * r_pll) {
			if (((m_pll / (2 * r_pll)) % 2) == 0) {
				phy->pll_pre_p =
					(m_pll / (2 * r_pll)) / 2 - 1;
				phy->pll_fbd_s =
					(m_pll / (2 * r_pll)) % 2 + 2;
			} else {
				phy->pll_pre_p =
					(m_pll / (2 * r_pll)) / 2;
				phy->pll_fbd_s =
					(m_pll / (2 * r_pll)) % 2;
			}
			phy->pll_fbd_div1f = 0;
			phy->pll_fbd_div5f = 0;
		} else {
			phy->pll_pre_p = 0;
			phy->pll_fbd_s = 0;
			phy->pll_fbd_div1f = 0;
			phy->pll_fbd_div5f = 1;
		}

		f_kHz = (u64)1000000000 * (u64)m_pll /
			((u64)ref_clk_ps * (u64)n_pll * (u64)q_pll);

		if (f_kHz >= req_kHz)
			break;

		tmp_kHz += 10;

	} while (true);

	return f_kHz;
}