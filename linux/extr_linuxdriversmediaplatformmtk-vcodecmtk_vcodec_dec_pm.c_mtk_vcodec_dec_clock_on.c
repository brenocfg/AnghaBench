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
struct mtk_vcodec_pm {int /*<<< orphan*/  larbvdec; int /*<<< orphan*/  vdecpll; int /*<<< orphan*/  vdec_sel; int /*<<< orphan*/  univpll_d2; int /*<<< orphan*/  clk_cci400_sel; int /*<<< orphan*/  vdec_bus_clk_src; int /*<<< orphan*/  venc_lt_sel; int /*<<< orphan*/  vencpll; int /*<<< orphan*/  vcodecpll; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int mtk_smi_larb_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int) ; 

void mtk_vcodec_dec_clock_on(struct mtk_vcodec_pm *pm)
{
	int ret;

	ret = clk_set_rate(pm->vcodecpll, 1482 * 1000000);
	if (ret)
		mtk_v4l2_err("clk_set_rate vcodecpll fail %d", ret);

	ret = clk_set_rate(pm->vencpll, 800 * 1000000);
	if (ret)
		mtk_v4l2_err("clk_set_rate vencpll fail %d", ret);

	ret = clk_prepare_enable(pm->vcodecpll);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable vcodecpll fail %d", ret);

	ret = clk_prepare_enable(pm->vencpll);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable vencpll fail %d", ret);

	ret = clk_prepare_enable(pm->vdec_bus_clk_src);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable vdec_bus_clk_src fail %d",
				ret);

	ret = clk_prepare_enable(pm->venc_lt_sel);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable venc_lt_sel fail %d", ret);

	ret = clk_set_parent(pm->venc_lt_sel, pm->vdec_bus_clk_src);
	if (ret)
		mtk_v4l2_err("clk_set_parent venc_lt_sel vdec_bus_clk_src fail %d",
				ret);

	ret = clk_prepare_enable(pm->univpll_d2);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable univpll_d2 fail %d", ret);

	ret = clk_prepare_enable(pm->clk_cci400_sel);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable clk_cci400_sel fail %d", ret);

	ret = clk_set_parent(pm->clk_cci400_sel, pm->univpll_d2);
	if (ret)
		mtk_v4l2_err("clk_set_parent clk_cci400_sel univpll_d2 fail %d",
				ret);

	ret = clk_prepare_enable(pm->vdecpll);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable vdecpll fail %d", ret);

	ret = clk_prepare_enable(pm->vdec_sel);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable vdec_sel fail %d", ret);

	ret = clk_set_parent(pm->vdec_sel, pm->vdecpll);
	if (ret)
		mtk_v4l2_err("clk_set_parent vdec_sel vdecpll fail %d", ret);

	ret = mtk_smi_larb_get(pm->larbvdec);
	if (ret)
		mtk_v4l2_err("mtk_smi_larb_get larbvdec fail %d", ret);

}