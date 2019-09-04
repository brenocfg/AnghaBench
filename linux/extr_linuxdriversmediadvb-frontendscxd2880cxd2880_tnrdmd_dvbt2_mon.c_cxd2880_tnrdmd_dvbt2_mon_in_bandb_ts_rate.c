#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
typedef  enum cxd2880_dvbt2_plp_btype { ____Placeholder_cxd2880_dvbt2_plp_btype } cxd2880_dvbt2_plp_btype ;
struct TYPE_6__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 int CXD2880_DVBT2_PLP_COMMON ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_mon_sync_stat (struct cxd2880_tnrdmd*,int*,int*,int*) ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub5 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt2_mon_in_bandb_ts_rate(struct cxd2880_tnrdmd
					      *tnr_dmd,
					      enum
					      cxd2880_dvbt2_plp_btype
					      type,
					      u32 *ts_rate_bps)
{
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 l1_post_ok = 0;
	u8 data[4];
	u8 addr = 0;

	int ret;

	if (!tnr_dmd || !ts_rate_bps)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		return -EINVAL;

	ret = slvt_freeze_reg(tnr_dmd);
	if (ret)
		return ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	if (!ts_lock) {
		slvt_unfreeze_reg(tnr_dmd);
		return -EAGAIN;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &l1_post_ok, 1);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	if (!(l1_post_ok & 0x01)) {
		slvt_unfreeze_reg(tnr_dmd);
		return -EAGAIN;
	}

	if (type == CXD2880_DVBT2_PLP_COMMON)
		addr = 0xba;
	else
		addr = 0xa7;

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addr, &data[0], 1);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	if ((data[0] & 0x80) == 0x00) {
		slvt_unfreeze_reg(tnr_dmd);
		return -EAGAIN;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x25);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	if (type == CXD2880_DVBT2_PLP_COMMON)
		addr = 0xa6;
	else
		addr = 0xaa;

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addr, &data[0], 4);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	*ts_rate_bps = ((data[0] & 0x07) << 24) | (data[1] << 16) |
		       (data[2] << 8) | data[3];

	return 0;
}