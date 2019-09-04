#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct cxd2880_tnrdmd {scalar_t__ state; scalar_t__ sys; int bandwidth; TYPE_1__* io; } ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EINVAL ; 
 int cxd2880_convert2s_complement (int,int) ; 
 int is_tps_locked (struct cxd2880_tnrdmd*) ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt_mon_carrier_offset(struct cxd2880_tnrdmd
					   *tnr_dmd, int *offset)
{
	u8 rdata[4];
	u32 ctl_val = 0;
	int ret;

	if (!tnr_dmd || !offset)
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
				     0x1d, rdata, 4);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	slvt_unfreeze_reg(tnr_dmd);

	ctl_val =
	    ((rdata[0] & 0x1f) << 24) | (rdata[1] << 16) | (rdata[2] << 8) |
	    (rdata[3]);
	*offset = cxd2880_convert2s_complement(ctl_val, 29);
	*offset = -1 * ((*offset) * tnr_dmd->bandwidth / 235);

	return ret;
}