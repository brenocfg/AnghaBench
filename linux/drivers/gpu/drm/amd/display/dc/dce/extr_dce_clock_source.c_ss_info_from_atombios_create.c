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
struct dce110_clk_src {int /*<<< orphan*/  lvds_ss_params_cnt; int /*<<< orphan*/  lvds_ss_params; int /*<<< orphan*/  dvi_ss_params_cnt; int /*<<< orphan*/  dvi_ss_params; int /*<<< orphan*/  hdmi_ss_params_cnt; int /*<<< orphan*/  hdmi_ss_params; int /*<<< orphan*/  dp_ss_params_cnt; int /*<<< orphan*/  dp_ss_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_SIGNAL_TYPE_DISPLAY_PORT ; 
 int /*<<< orphan*/  AS_SIGNAL_TYPE_DVI ; 
 int /*<<< orphan*/  AS_SIGNAL_TYPE_HDMI ; 
 int /*<<< orphan*/  AS_SIGNAL_TYPE_LVDS ; 
 int /*<<< orphan*/  get_ss_info_from_atombios (struct dce110_clk_src*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ss_info_from_atombios_create(
	struct dce110_clk_src *clk_src)
{
	get_ss_info_from_atombios(
		clk_src,
		AS_SIGNAL_TYPE_DISPLAY_PORT,
		&clk_src->dp_ss_params,
		&clk_src->dp_ss_params_cnt);
	get_ss_info_from_atombios(
		clk_src,
		AS_SIGNAL_TYPE_HDMI,
		&clk_src->hdmi_ss_params,
		&clk_src->hdmi_ss_params_cnt);
	get_ss_info_from_atombios(
		clk_src,
		AS_SIGNAL_TYPE_DVI,
		&clk_src->dvi_ss_params,
		&clk_src->dvi_ss_params_cnt);
	get_ss_info_from_atombios(
		clk_src,
		AS_SIGNAL_TYPE_LVDS,
		&clk_src->lvds_ss_params,
		&clk_src->lvds_ss_params_cnt);
}