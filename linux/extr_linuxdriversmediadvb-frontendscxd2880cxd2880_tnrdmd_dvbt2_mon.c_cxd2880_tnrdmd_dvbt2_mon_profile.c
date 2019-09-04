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
struct cxd2880_tnrdmd {scalar_t__ state; scalar_t__ sys; scalar_t__ diver_mode; struct cxd2880_tnrdmd* diver_sub; TYPE_1__* io; } ;
typedef  enum cxd2880_dvbt2_profile { ____Placeholder_cxd2880_dvbt2_profile } cxd2880_dvbt2_profile ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 int CXD2880_DVBT2_PROFILE_BASE ; 
 int CXD2880_DVBT2_PROFILE_LITE ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt2_mon_profile(struct cxd2880_tnrdmd
				     *tnr_dmd,
				     enum cxd2880_dvbt2_profile
				     *profile)
{
	u8 data;
	int ret;

	if (!tnr_dmd || !profile)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (ret)
		return ret;

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x22, &data, sizeof(data));
	if (ret)
		return ret;

	if (data & 0x02) {
		if (data & 0x01)
			*profile = CXD2880_DVBT2_PROFILE_LITE;
		else
			*profile = CXD2880_DVBT2_PROFILE_BASE;
	} else {
		ret = -EAGAIN;
		if (tnr_dmd->diver_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN)
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_profile(tnr_dmd->diver_sub,
							     profile);

		return ret;
	}

	return 0;
}