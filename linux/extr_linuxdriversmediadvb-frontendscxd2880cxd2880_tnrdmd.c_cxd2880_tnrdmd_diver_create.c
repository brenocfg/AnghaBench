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
struct cxd2880_tnrdmd_diver_create_param {int /*<<< orphan*/  stationary_use; int /*<<< orphan*/  is_cxd2881gg; int /*<<< orphan*/  xosc_i_sub; int /*<<< orphan*/  ts_output_if; int /*<<< orphan*/  en_internal_ldo; int /*<<< orphan*/  xosc_i_main; scalar_t__ xosc_cap_main; } ;
struct cxd2880_tnrdmd_create_param {int /*<<< orphan*/  stationary_use; int /*<<< orphan*/  is_cxd2881gg; int /*<<< orphan*/  xosc_i; scalar_t__ xosc_cap; int /*<<< orphan*/  xtal_share_type; int /*<<< orphan*/  ts_output_if; int /*<<< orphan*/  en_internal_ldo; } ;
struct cxd2880_tnrdmd {int srl_ts_clk_mod_cnts; int en_fef_intmtnt_base; int en_fef_intmtnt_lite; int /*<<< orphan*/ * lna_thrs_tbl_cable; int /*<<< orphan*/ * lna_thrs_tbl_air; int /*<<< orphan*/ * rf_lvl_cmpstn; struct cxd2880_tnrdmd* diver_sub; int /*<<< orphan*/  diver_mode; struct cxd2880_io* io; struct cxd2880_tnrdmd_create_param create_param; } ;
struct cxd2880_io {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_DIVERMODE_SUB ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_XTAL_SHARE_MASTER ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_XTAL_SHARE_SLAVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int) ; 

int cxd2880_tnrdmd_diver_create(struct cxd2880_tnrdmd
				*tnr_dmd_main,
				struct cxd2880_io *io_main,
				struct cxd2880_tnrdmd *tnr_dmd_sub,
				struct cxd2880_io *io_sub,
				struct
				cxd2880_tnrdmd_diver_create_param
				*create_param)
{
	struct cxd2880_tnrdmd_create_param *main_param, *sub_param;

	if (!tnr_dmd_main || !io_main || !tnr_dmd_sub || !io_sub ||
	    !create_param)
		return -EINVAL;

	memset(tnr_dmd_main, 0, sizeof(struct cxd2880_tnrdmd));
	memset(tnr_dmd_sub, 0, sizeof(struct cxd2880_tnrdmd));

	main_param = &tnr_dmd_main->create_param;
	sub_param = &tnr_dmd_sub->create_param;

	tnr_dmd_main->io = io_main;
	tnr_dmd_main->diver_mode = CXD2880_TNRDMD_DIVERMODE_MAIN;
	tnr_dmd_main->diver_sub = tnr_dmd_sub;
	tnr_dmd_main->create_param.en_internal_ldo =
	    create_param->en_internal_ldo;

	main_param->ts_output_if = create_param->ts_output_if;
	main_param->xtal_share_type = CXD2880_TNRDMD_XTAL_SHARE_MASTER;
	main_param->xosc_cap = create_param->xosc_cap_main;
	main_param->xosc_i = create_param->xosc_i_main;
	main_param->is_cxd2881gg = create_param->is_cxd2881gg;
	main_param->stationary_use = create_param->stationary_use;

	tnr_dmd_sub->io = io_sub;
	tnr_dmd_sub->diver_mode = CXD2880_TNRDMD_DIVERMODE_SUB;
	tnr_dmd_sub->diver_sub = NULL;

	sub_param->en_internal_ldo = create_param->en_internal_ldo;
	sub_param->ts_output_if = create_param->ts_output_if;
	sub_param->xtal_share_type = CXD2880_TNRDMD_XTAL_SHARE_SLAVE;
	sub_param->xosc_cap = 0;
	sub_param->xosc_i = create_param->xosc_i_sub;
	sub_param->is_cxd2881gg = create_param->is_cxd2881gg;
	sub_param->stationary_use = create_param->stationary_use;

	tnr_dmd_main->srl_ts_clk_mod_cnts = 1;
	tnr_dmd_main->en_fef_intmtnt_base = 1;
	tnr_dmd_main->en_fef_intmtnt_lite = 1;
	tnr_dmd_main->rf_lvl_cmpstn = NULL;
	tnr_dmd_main->lna_thrs_tbl_air = NULL;
	tnr_dmd_main->lna_thrs_tbl_cable = NULL;

	tnr_dmd_sub->srl_ts_clk_mod_cnts = 1;
	tnr_dmd_sub->en_fef_intmtnt_base = 1;
	tnr_dmd_sub->en_fef_intmtnt_lite = 1;
	tnr_dmd_sub->rf_lvl_cmpstn = NULL;
	tnr_dmd_sub->lna_thrs_tbl_air = NULL;
	tnr_dmd_sub->lna_thrs_tbl_cable = NULL;

	return 0;
}