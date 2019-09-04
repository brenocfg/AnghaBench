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
struct cxd2880_tnrdmd {scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt_mon_sync_stat(struct cxd2880_tnrdmd
				      *tnr_dmd, u8 *sync_stat,
				      u8 *ts_lock_stat,
				      u8 *unlock_detected)
{
	u8 rdata = 0x00;
	int ret;

	if (!tnr_dmd || !sync_stat || !ts_lock_stat || !unlock_detected)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;
	if (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (ret)
		return ret;

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, &rdata, 1);
	if (ret)
		return ret;

	*unlock_detected = (rdata & 0x10) ? 1 : 0;
	*sync_stat = rdata & 0x07;
	*ts_lock_stat = (rdata & 0x20) ? 1 : 0;

	if (*sync_stat == 0x07)
		return -EAGAIN;

	return ret;
}