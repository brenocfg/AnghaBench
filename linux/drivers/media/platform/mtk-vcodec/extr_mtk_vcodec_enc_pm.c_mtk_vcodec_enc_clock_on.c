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
struct mtk_vcodec_clk {int clk_num; TYPE_1__* clk_info; } ;
struct mtk_vcodec_pm {int /*<<< orphan*/  larbvenc; int /*<<< orphan*/  larbvenclt; struct mtk_vcodec_clk venc_clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  vcodec_clk; int /*<<< orphan*/  clk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int mtk_smi_larb_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_smi_larb_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int,...) ; 

void mtk_vcodec_enc_clock_on(struct mtk_vcodec_pm *pm)
{
	struct mtk_vcodec_clk *enc_clk = &pm->venc_clk;
	int ret, i = 0;

	for (i = 0; i < enc_clk->clk_num; i++) {
		ret = clk_prepare_enable(enc_clk->clk_info[i].vcodec_clk);
		if (ret) {
			mtk_v4l2_err("venc clk_prepare_enable %d %s fail %d", i,
				enc_clk->clk_info[i].clk_name, ret);
			goto clkerr;
		}
	}

	ret = mtk_smi_larb_get(pm->larbvenc);
	if (ret) {
		mtk_v4l2_err("mtk_smi_larb_get larb3 fail %d", ret);
		goto larbvencerr;
	}
	ret = mtk_smi_larb_get(pm->larbvenclt);
	if (ret) {
		mtk_v4l2_err("mtk_smi_larb_get larb4 fail %d", ret);
		goto larbvenclterr;
	}
	return;

larbvenclterr:
	mtk_smi_larb_put(pm->larbvenc);
larbvencerr:
clkerr:
	for (i -= 1; i >= 0; i--)
		clk_disable_unprepare(enc_clk->clk_info[i].vcodec_clk);
}