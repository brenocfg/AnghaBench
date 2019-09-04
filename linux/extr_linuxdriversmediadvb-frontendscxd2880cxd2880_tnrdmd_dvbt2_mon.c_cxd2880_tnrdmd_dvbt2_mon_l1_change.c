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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_5__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_mon_sync_stat (struct cxd2880_tnrdmd*,int*,int*,int*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub (struct cxd2880_tnrdmd*,int*,int*) ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

int cxd2880_tnrdmd_dvbt2_mon_l1_change(struct cxd2880_tnrdmd
				       *tnr_dmd, u8 *l1_change)
{
	u8 data;
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	int ret;

	if (!tnr_dmd || !l1_change)
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

	if (sync_state < 5) {
		if (tnr_dmd->diver_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN) {
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub
			    (tnr_dmd, &sync_state, &unlock_detected);
			if (ret) {
				slvt_unfreeze_reg(tnr_dmd);
				return ret;
			}

			if (sync_state < 5) {
				slvt_unfreeze_reg(tnr_dmd);
				return -EAGAIN;
			}
		} else {
			slvt_unfreeze_reg(tnr_dmd);
			return -EAGAIN;
		}
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
				     0x5f, &data, sizeof(data));
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	*l1_change = data & 0x01;
	if (*l1_change) {
		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x22);
		if (ret) {
			slvt_unfreeze_reg(tnr_dmd);
			return ret;
		}

		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x16, 0x01);
		if (ret) {
			slvt_unfreeze_reg(tnr_dmd);
			return ret;
		}
	}
	slvt_unfreeze_reg(tnr_dmd);

	return 0;
}