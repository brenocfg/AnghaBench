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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
typedef  enum cxd2880_dvbt2_plp_constell { ____Placeholder_cxd2880_dvbt2_plp_constell } cxd2880_dvbt2_plp_constell ;
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
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub5 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt2_mon_qam(struct cxd2880_tnrdmd *tnr_dmd,
				 enum cxd2880_dvbt2_plp_btype type,
				 enum cxd2880_dvbt2_plp_constell *qam)
{
	u8 data;
	u8 l1_post_ok = 0;
	int ret;

	if (!tnr_dmd || !qam)
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

	if (type == CXD2880_DVBT2_PLP_COMMON) {
		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb6, &data, 1);
		if (ret) {
			slvt_unfreeze_reg(tnr_dmd);
			return ret;
		}

		if (data == 0) {
			slvt_unfreeze_reg(tnr_dmd);
			return -EAGAIN;
		}

		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb1, &data, 1);
		if (ret) {
			slvt_unfreeze_reg(tnr_dmd);
			return ret;
		}
	} else {
		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x9e, &data, 1);
		if (ret) {
			slvt_unfreeze_reg(tnr_dmd);
			return ret;
		}
	}

	slvt_unfreeze_reg(tnr_dmd);

	*qam = (enum cxd2880_dvbt2_plp_constell)(data & 0x07);

	return ret;
}