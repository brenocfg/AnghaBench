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
typedef  int /*<<< orphan*/  u32 ;
struct vop_win_data {int dummy; } ;
struct vop_win {struct vop_win_data* data; } ;
struct vop {int len; int is_enabled; int /*<<< orphan*/  dev; struct reset_control* dclk; struct reset_control* hclk; struct reset_control* aclk; struct reset_control* dclk_rst; struct vop_win* win; TYPE_1__* data; scalar_t__ regs; int /*<<< orphan*/ * regsbak; } ;
struct reset_control {int dummy; } ;
struct TYPE_2__ {int win_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  INTR_MASK ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  VOP_INTR_SET_TYPE (struct vop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VOP_REG_SET (struct vop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VOP_WIN_SET (struct vop*,struct vop_win_data const*,int,int) ; 
 int /*<<< orphan*/  clear ; 
 int /*<<< orphan*/  clk_disable (struct reset_control*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct reset_control*) ; 
 int clk_prepare (struct reset_control*) ; 
 int clk_prepare_enable (struct reset_control*) ; 
 int /*<<< orphan*/  clk_unprepare (struct reset_control*) ; 
 int /*<<< orphan*/  common ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 void* devm_reset_control_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsp_blank ; 
 int /*<<< orphan*/  enable ; 
 int gate ; 
 int /*<<< orphan*/  global_regdone_en ; 
 int /*<<< orphan*/  misc ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  vop_cfg_done (struct vop*) ; 
 int /*<<< orphan*/  vop_win_disable (struct vop*,struct vop_win*) ; 

__attribute__((used)) static int vop_initial(struct vop *vop)
{
	struct reset_control *ahb_rst;
	int i, ret;

	vop->hclk = devm_clk_get(vop->dev, "hclk_vop");
	if (IS_ERR(vop->hclk)) {
		DRM_DEV_ERROR(vop->dev, "failed to get hclk source\n");
		return PTR_ERR(vop->hclk);
	}
	vop->aclk = devm_clk_get(vop->dev, "aclk_vop");
	if (IS_ERR(vop->aclk)) {
		DRM_DEV_ERROR(vop->dev, "failed to get aclk source\n");
		return PTR_ERR(vop->aclk);
	}
	vop->dclk = devm_clk_get(vop->dev, "dclk_vop");
	if (IS_ERR(vop->dclk)) {
		DRM_DEV_ERROR(vop->dev, "failed to get dclk source\n");
		return PTR_ERR(vop->dclk);
	}

	ret = pm_runtime_get_sync(vop->dev);
	if (ret < 0) {
		DRM_DEV_ERROR(vop->dev, "failed to get pm runtime: %d\n", ret);
		return ret;
	}

	ret = clk_prepare(vop->dclk);
	if (ret < 0) {
		DRM_DEV_ERROR(vop->dev, "failed to prepare dclk\n");
		goto err_put_pm_runtime;
	}

	/* Enable both the hclk and aclk to setup the vop */
	ret = clk_prepare_enable(vop->hclk);
	if (ret < 0) {
		DRM_DEV_ERROR(vop->dev, "failed to prepare/enable hclk\n");
		goto err_unprepare_dclk;
	}

	ret = clk_prepare_enable(vop->aclk);
	if (ret < 0) {
		DRM_DEV_ERROR(vop->dev, "failed to prepare/enable aclk\n");
		goto err_disable_hclk;
	}

	/*
	 * do hclk_reset, reset all vop registers.
	 */
	ahb_rst = devm_reset_control_get(vop->dev, "ahb");
	if (IS_ERR(ahb_rst)) {
		DRM_DEV_ERROR(vop->dev, "failed to get ahb reset\n");
		ret = PTR_ERR(ahb_rst);
		goto err_disable_aclk;
	}
	reset_control_assert(ahb_rst);
	usleep_range(10, 20);
	reset_control_deassert(ahb_rst);

	VOP_INTR_SET_TYPE(vop, clear, INTR_MASK, 1);
	VOP_INTR_SET_TYPE(vop, enable, INTR_MASK, 0);

	for (i = 0; i < vop->len; i += sizeof(u32))
		vop->regsbak[i / 4] = readl_relaxed(vop->regs + i);

	VOP_REG_SET(vop, misc, global_regdone_en, 1);
	VOP_REG_SET(vop, common, dsp_blank, 0);

	for (i = 0; i < vop->data->win_size; i++) {
		struct vop_win *vop_win = &vop->win[i];
		const struct vop_win_data *win = vop_win->data;
		int channel = i * 2 + 1;

		VOP_WIN_SET(vop, win, channel, (channel + 1) << 4 | channel);
		vop_win_disable(vop, vop_win);
		VOP_WIN_SET(vop, win, gate, 1);
	}

	vop_cfg_done(vop);

	/*
	 * do dclk_reset, let all config take affect.
	 */
	vop->dclk_rst = devm_reset_control_get(vop->dev, "dclk");
	if (IS_ERR(vop->dclk_rst)) {
		DRM_DEV_ERROR(vop->dev, "failed to get dclk reset\n");
		ret = PTR_ERR(vop->dclk_rst);
		goto err_disable_aclk;
	}
	reset_control_assert(vop->dclk_rst);
	usleep_range(10, 20);
	reset_control_deassert(vop->dclk_rst);

	clk_disable(vop->hclk);
	clk_disable(vop->aclk);

	vop->is_enabled = false;

	pm_runtime_put_sync(vop->dev);

	return 0;

err_disable_aclk:
	clk_disable_unprepare(vop->aclk);
err_disable_hclk:
	clk_disable_unprepare(vop->hclk);
err_unprepare_dclk:
	clk_unprepare(vop->dclk);
err_put_pm_runtime:
	pm_runtime_put_sync(vop->dev);
	return ret;
}