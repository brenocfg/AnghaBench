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
struct cxd2880_tnrdmd_create_param {int dummy; } ;
struct cxd2880_tnrdmd {int srl_ts_clk_mod_cnts; int en_fef_intmtnt_base; int en_fef_intmtnt_lite; int /*<<< orphan*/  cancel; int /*<<< orphan*/ * lna_thrs_tbl_cable; int /*<<< orphan*/ * lna_thrs_tbl_air; int /*<<< orphan*/ * rf_lvl_cmpstn; int /*<<< orphan*/ * diver_sub; int /*<<< orphan*/  diver_mode; struct cxd2880_tnrdmd_create_param create_param; struct cxd2880_io* io; } ;
struct cxd2880_io {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_TNRDMD_DIVERMODE_SINGLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int) ; 

int cxd2880_tnrdmd_create(struct cxd2880_tnrdmd *tnr_dmd,
			  struct cxd2880_io *io,
			  struct cxd2880_tnrdmd_create_param
			  *create_param)
{
	if (!tnr_dmd || !io || !create_param)
		return -EINVAL;

	memset(tnr_dmd, 0, sizeof(struct cxd2880_tnrdmd));

	tnr_dmd->io = io;
	tnr_dmd->create_param = *create_param;

	tnr_dmd->diver_mode = CXD2880_TNRDMD_DIVERMODE_SINGLE;
	tnr_dmd->diver_sub = NULL;

	tnr_dmd->srl_ts_clk_mod_cnts = 1;
	tnr_dmd->en_fef_intmtnt_base = 1;
	tnr_dmd->en_fef_intmtnt_lite = 1;
	tnr_dmd->rf_lvl_cmpstn = NULL;
	tnr_dmd->lna_thrs_tbl_air = NULL;
	tnr_dmd->lna_thrs_tbl_cable = NULL;
	atomic_set(&tnr_dmd->cancel, 0);

	return 0;
}