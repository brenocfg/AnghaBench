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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; TYPE_1__* io; } ;
struct cxd2880_dvbt2_ofdm {int /*<<< orphan*/  mixed; } ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* write_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SINGLE ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_mon_ofdm (struct cxd2880_tnrdmd*,struct cxd2880_dvbt2_ofdm*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int const*,int) ; 

int cxd2880_tnrdmd_dvbt2_diver_fef_setting(struct cxd2880_tnrdmd
					   *tnr_dmd)
{
	struct cxd2880_dvbt2_ofdm ofdm;
	static const u8 data[] = { 0, 8, 0, 16, 0, 32, 0, 64, 0, 128, 1, 0};
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE)
		return 0;

	ret = cxd2880_tnrdmd_dvbt2_mon_ofdm(tnr_dmd, &ofdm);
	if (ret)
		return ret;

	if (!ofdm.mixed)
		return 0;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x1d);
	if (ret)
		return ret;

	return tnr_dmd->io->write_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_DMD,
				       0x47, data, 12);
}