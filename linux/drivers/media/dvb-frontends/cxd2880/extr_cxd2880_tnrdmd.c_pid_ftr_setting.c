#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cxd2880_tnrdmd_pid_ftr_cfg {TYPE_1__* pid_cfg; scalar_t__ is_negative; } ;
struct cxd2880_tnrdmd {TYPE_2__* io; } ;
struct TYPE_6__ {int (* write_reg ) (TYPE_2__*,int /*<<< orphan*/ ,int,int) ;int (* write_regs ) (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ;} ;
struct TYPE_5__ {int pid; scalar_t__ is_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int EINVAL ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub3 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int pid_ftr_setting(struct cxd2880_tnrdmd *tnr_dmd,
			   struct cxd2880_tnrdmd_pid_ftr_cfg
			   *pid_ftr_cfg)
{
	int i;
	int ret;
	u8 data[65];

	if (!tnr_dmd)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	if (ret)
		return ret;

	if (!pid_ftr_cfg)
		return tnr_dmd->io->write_reg(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x50, 0x02);

	data[0] = pid_ftr_cfg->is_negative ? 0x01 : 0x00;

	for (i = 0; i < 32; i++) {
		if (pid_ftr_cfg->pid_cfg[i].is_en) {
			data[1 + (i * 2)] = (pid_ftr_cfg->pid_cfg[i].pid >> 8) | 0x20;
			data[2 + (i * 2)] =  pid_ftr_cfg->pid_cfg[i].pid & 0xff;
		} else {
			data[1 + (i * 2)] = 0x00;
			data[2 + (i * 2)] = 0x00;
		}
	}

	return tnr_dmd->io->write_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_DMD,
				       0x50, data, 65);
}