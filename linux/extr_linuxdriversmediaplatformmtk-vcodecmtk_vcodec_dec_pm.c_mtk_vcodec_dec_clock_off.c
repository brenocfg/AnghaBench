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
struct mtk_vcodec_pm {int /*<<< orphan*/  vcodecpll; int /*<<< orphan*/  vencpll; int /*<<< orphan*/  vdec_bus_clk_src; int /*<<< orphan*/  venc_lt_sel; int /*<<< orphan*/  clk_cci400_sel; int /*<<< orphan*/  univpll_d2; int /*<<< orphan*/  vdecpll; int /*<<< orphan*/  vdec_sel; int /*<<< orphan*/  larbvdec; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_smi_larb_put (int /*<<< orphan*/ ) ; 

void mtk_vcodec_dec_clock_off(struct mtk_vcodec_pm *pm)
{
	mtk_smi_larb_put(pm->larbvdec);
	clk_disable_unprepare(pm->vdec_sel);
	clk_disable_unprepare(pm->vdecpll);
	clk_disable_unprepare(pm->univpll_d2);
	clk_disable_unprepare(pm->clk_cci400_sel);
	clk_disable_unprepare(pm->venc_lt_sel);
	clk_disable_unprepare(pm->vdec_bus_clk_src);
	clk_disable_unprepare(pm->vencpll);
	clk_disable_unprepare(pm->vcodecpll);
}