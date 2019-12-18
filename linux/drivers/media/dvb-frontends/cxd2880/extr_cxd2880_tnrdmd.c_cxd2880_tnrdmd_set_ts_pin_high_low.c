#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {scalar_t__ ts_output_if; } ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; TYPE_2__* io; TYPE_1__ create_param; } ;
struct TYPE_7__ {int (* write_reg ) (TYPE_2__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 scalar_t__ CXD2880_TNRDMD_TSOUT_IF_TS ; 
 int EINVAL ; 
 int ENOTTY ; 
 int cxd2880_io_write_multi_regs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int load_cfg_mem (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  set_ts_pin_seq ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub3 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 

int cxd2880_tnrdmd_set_ts_pin_high_low(struct cxd2880_tnrdmd
				       *tnr_dmd, u8 en, u8 value)
{
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
		return -EINVAL;

	if (tnr_dmd->create_param.ts_output_if != CXD2880_TNRDMD_TSOUT_IF_TS)
		return -ENOTTY;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	if (ret)
		return ret;

	if (en) {
		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x50, ((value & 0x1f) | 0x80));
		if (ret)
			return ret;

		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x52, (value & 0x1f));
	} else {
		ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
						  CXD2880_IO_TGT_SYS,
						  set_ts_pin_seq,
						  ARRAY_SIZE(set_ts_pin_seq));
		if (ret)
			return ret;

		ret = load_cfg_mem(tnr_dmd);
	}

	return ret;
}