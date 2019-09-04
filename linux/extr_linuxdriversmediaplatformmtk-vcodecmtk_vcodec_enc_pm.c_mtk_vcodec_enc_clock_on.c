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
struct mtk_vcodec_pm {int /*<<< orphan*/  larbvenclt; int /*<<< orphan*/  larbvenc; int /*<<< orphan*/  univpll1_d2; int /*<<< orphan*/  venc_lt_sel; int /*<<< orphan*/  vencpll_d2; int /*<<< orphan*/  venc_sel; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtk_smi_larb_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int) ; 

void mtk_vcodec_enc_clock_on(struct mtk_vcodec_pm *pm)
{
	int ret;

	ret = clk_prepare_enable(pm->venc_sel);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable fail %d", ret);

	ret = clk_set_parent(pm->venc_sel, pm->vencpll_d2);
	if (ret)
		mtk_v4l2_err("clk_set_parent fail %d", ret);

	ret = clk_prepare_enable(pm->venc_lt_sel);
	if (ret)
		mtk_v4l2_err("clk_prepare_enable fail %d", ret);

	ret = clk_set_parent(pm->venc_lt_sel, pm->univpll1_d2);
	if (ret)
		mtk_v4l2_err("clk_set_parent fail %d", ret);

	ret = mtk_smi_larb_get(pm->larbvenc);
	if (ret)
		mtk_v4l2_err("mtk_smi_larb_get larb3 fail %d", ret);

	ret = mtk_smi_larb_get(pm->larbvenclt);
	if (ret)
		mtk_v4l2_err("mtk_smi_larb_get larb4 fail %d", ret);

}