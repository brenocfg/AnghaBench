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
struct mtk_vcodec_pm {int /*<<< orphan*/  venc_sel; int /*<<< orphan*/  venc_lt_sel; int /*<<< orphan*/  larbvenclt; int /*<<< orphan*/  larbvenc; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_smi_larb_put (int /*<<< orphan*/ ) ; 

void mtk_vcodec_enc_clock_off(struct mtk_vcodec_pm *pm)
{
	mtk_smi_larb_put(pm->larbvenc);
	mtk_smi_larb_put(pm->larbvenclt);
	clk_disable_unprepare(pm->venc_lt_sel);
	clk_disable_unprepare(pm->venc_sel);
}