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
typedef  int u32 ;
struct cxd2880_tnrdmd {scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
typedef  int s8 ;
typedef  int /*<<< orphan*/  nominal_rate_reg ;
typedef  int /*<<< orphan*/  ctl_val_reg ;
struct TYPE_5__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int is_tps_locked (struct cxd2880_tnrdmd*) ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt_mon_sampling_offset(struct cxd2880_tnrdmd
					    *tnr_dmd, int *ppm)
{
	u8 ctl_val_reg[5];
	u8 nominal_rate_reg[5];
	u32 trl_ctl_val = 0;
	u32 trcg_nominal_rate = 0;
	int num;
	int den;
	s8 diff_upper = 0;
	int ret;

	if (!tnr_dmd || !ppm)
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
				     0x21, ctl_val_reg,
				     sizeof(ctl_val_reg));
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x60, nominal_rate_reg,
				     sizeof(nominal_rate_reg));
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	slvt_unfreeze_reg(tnr_dmd);

	diff_upper =
	    (ctl_val_reg[0] & 0x7f) - (nominal_rate_reg[0] & 0x7f);

	if (diff_upper < -1 || diff_upper > 1)
		return -EAGAIN;

	trl_ctl_val = ctl_val_reg[1] << 24;
	trl_ctl_val |= ctl_val_reg[2] << 16;
	trl_ctl_val |= ctl_val_reg[3] << 8;
	trl_ctl_val |= ctl_val_reg[4];

	trcg_nominal_rate = nominal_rate_reg[1] << 24;
	trcg_nominal_rate |= nominal_rate_reg[2] << 16;
	trcg_nominal_rate |= nominal_rate_reg[3] << 8;
	trcg_nominal_rate |= nominal_rate_reg[4];

	trl_ctl_val >>= 1;
	trcg_nominal_rate >>= 1;

	if (diff_upper == 1)
		num =
		    (int)((trl_ctl_val + 0x80000000u) -
			  trcg_nominal_rate);
	else if (diff_upper == -1)
		num =
		    -(int)((trcg_nominal_rate + 0x80000000u) -
			   trl_ctl_val);
	else
		num = (int)(trl_ctl_val - trcg_nominal_rate);

	den = (nominal_rate_reg[0] & 0x7f) << 24;
	den |= nominal_rate_reg[1] << 16;
	den |= nominal_rate_reg[2] << 8;
	den |= nominal_rate_reg[3];
	den = (den + (390625 / 2)) / 390625;

	den >>= 1;

	if (num >= 0)
		*ppm = (num + (den / 2)) / den;
	else
		*ppm = (num - (den / 2)) / den;

	return ret;
}