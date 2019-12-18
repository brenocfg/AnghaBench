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
struct cxd2880_tnrdmd {TYPE_1__* io; } ;
typedef  enum cxd2880_dvbt_profile { ____Placeholder_cxd2880_dvbt_profile } cxd2880_dvbt_profile ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int CXD2880_DVBT_PROFILE_HP ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int EINVAL ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int dvbt_set_profile(struct cxd2880_tnrdmd *tnr_dmd,
			    enum cxd2880_dvbt_profile profile)
{
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x10);
	if (ret)
		return ret;

	return tnr_dmd->io->write_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x67,
				      (profile == CXD2880_DVBT_PROFILE_HP)
				      ? 0x00 : 0x01);
}