#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cxd2880_tnrdmd {scalar_t__ state; scalar_t__ sys; scalar_t__ diver_mode; TYPE_1__* io; struct cxd2880_tnrdmd* diver_sub; } ;
struct cxd2880_dvbt_tpsinfo {int constellation; int hierarchy; int rate_hp; int rate_lp; int guard; int mode; int fnum; int length_indicator; int cell_id; int reserved_even; int reserved_odd; int cell_id_ok; } ;
typedef  enum cxd2880_dvbt_mode { ____Placeholder_cxd2880_dvbt_mode } cxd2880_dvbt_mode ;
typedef  enum cxd2880_dvbt_hierarchy { ____Placeholder_cxd2880_dvbt_hierarchy } cxd2880_dvbt_hierarchy ;
typedef  enum cxd2880_dvbt_guard { ____Placeholder_cxd2880_dvbt_guard } cxd2880_dvbt_guard ;
typedef  enum cxd2880_dvbt_constellation { ____Placeholder_cxd2880_dvbt_constellation } cxd2880_dvbt_constellation ;
typedef  enum cxd2880_dvbt_coderate { ____Placeholder_cxd2880_dvbt_coderate } cxd2880_dvbt_coderate ;
struct TYPE_5__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EINVAL ; 
 int is_tps_locked (struct cxd2880_tnrdmd*) ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt_mon_tps_info(struct cxd2880_tnrdmd
				     *tnr_dmd,
				     struct cxd2880_dvbt_tpsinfo
				     *info)
{
	u8 rdata[7];
	u8 cell_id_ok = 0;
	int ret;

	if (!tnr_dmd || !info)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		return -EINVAL;

	ret = slvt_freeze_reg(tnr_dmd);
	if (ret)
		return ret;

	ret = is_tps_locked(tnr_dmd);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);

		if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
			ret =
			    cxd2880_tnrdmd_dvbt_mon_tps_info(tnr_dmd->diver_sub,
							     info);

		return ret;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x29, rdata, 7);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x11);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xd5, &cell_id_ok, 1);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	slvt_unfreeze_reg(tnr_dmd);

	info->constellation =
	    (enum cxd2880_dvbt_constellation)((rdata[0] >> 6) & 0x03);
	info->hierarchy = (enum cxd2880_dvbt_hierarchy)((rdata[0] >> 3) & 0x07);
	info->rate_hp = (enum cxd2880_dvbt_coderate)(rdata[0] & 0x07);
	info->rate_lp = (enum cxd2880_dvbt_coderate)((rdata[1] >> 5) & 0x07);
	info->guard = (enum cxd2880_dvbt_guard)((rdata[1] >> 3) & 0x03);
	info->mode = (enum cxd2880_dvbt_mode)((rdata[1] >> 1) & 0x03);
	info->fnum = (rdata[2] >> 6) & 0x03;
	info->length_indicator = rdata[2] & 0x3f;
	info->cell_id = (rdata[3] << 8) | rdata[4];
	info->reserved_even = rdata[5] & 0x3f;
	info->reserved_odd = rdata[6] & 0x3f;

	info->cell_id_ok = cell_id_ok & 0x01;

	return ret;
}