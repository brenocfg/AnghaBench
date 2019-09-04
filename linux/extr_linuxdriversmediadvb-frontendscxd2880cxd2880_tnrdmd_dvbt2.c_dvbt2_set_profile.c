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
struct cxd2880_tnrdmd {int clk_mode; TYPE_1__* io; } ;
typedef  enum cxd2880_dvbt2_profile { ____Placeholder_cxd2880_dvbt2_profile } cxd2880_dvbt2_profile ;
struct TYPE_5__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
#define  CXD2880_DVBT2_PROFILE_ANY 133 
#define  CXD2880_DVBT2_PROFILE_BASE 132 
#define  CXD2880_DVBT2_PROFILE_LITE 131 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
#define  CXD2880_TNRDMD_CLOCKMODE_A 130 
#define  CXD2880_TNRDMD_CLOCKMODE_B 129 
#define  CXD2880_TNRDMD_CLOCKMODE_C 128 
 int EINVAL ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int dvbt2_set_profile(struct cxd2880_tnrdmd *tnr_dmd,
			     enum cxd2880_dvbt2_profile profile)
{
	u8 t2_mode_tune_mode = 0;
	u8 seq_not2_dtime = 0;
	u8 dtime1 = 0;
	u8 dtime2 = 0;
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	switch (tnr_dmd->clk_mode) {
	case CXD2880_TNRDMD_CLOCKMODE_A:
		dtime1 = 0x27;
		dtime2 = 0x0c;
		break;
	case CXD2880_TNRDMD_CLOCKMODE_B:
		dtime1 = 0x2c;
		dtime2 = 0x0d;
		break;
	case CXD2880_TNRDMD_CLOCKMODE_C:
		dtime1 = 0x2e;
		dtime2 = 0x0e;
		break;
	default:
		return -EINVAL;
	}

	switch (profile) {
	case CXD2880_DVBT2_PROFILE_BASE:
		t2_mode_tune_mode = 0x01;
		seq_not2_dtime = dtime2;
		break;

	case CXD2880_DVBT2_PROFILE_LITE:
		t2_mode_tune_mode = 0x05;
		seq_not2_dtime = dtime1;
		break;

	case CXD2880_DVBT2_PROFILE_ANY:
		t2_mode_tune_mode = 0x00;
		seq_not2_dtime = dtime1;
		break;

	default:
		return -EINVAL;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x2e);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, t2_mode_tune_mode);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	if (ret)
		return ret;

	return tnr_dmd->io->write_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x2c, seq_not2_dtime);
}