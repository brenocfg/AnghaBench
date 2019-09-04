#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int ts_output_if; } ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; int /*<<< orphan*/  io; TYPE_1__ create_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
#define  CXD2880_TNRDMD_TSOUT_IF_SDIO 130 
#define  CXD2880_TNRDMD_TSOUT_IF_SPI 129 
#define  CXD2880_TNRDMD_TSOUT_IF_TS 128 
 int EINVAL ; 
 int cxd2880_io_write_multi_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ts_output_seq1 ; 
 int /*<<< orphan*/  set_ts_output_seq2 ; 
 int /*<<< orphan*/  set_ts_output_seq3 ; 
 int /*<<< orphan*/  set_ts_output_seq4 ; 

int cxd2880_tnrdmd_set_ts_output(struct cxd2880_tnrdmd *tnr_dmd,
				 u8 en)
{
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	switch (tnr_dmd->create_param.ts_output_if) {
	case CXD2880_TNRDMD_TSOUT_IF_TS:
		if (en) {
			ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
							  CXD2880_IO_TGT_SYS,
							  set_ts_output_seq1,
							  ARRAY_SIZE(set_ts_output_seq1));
			if (ret)
				return ret;

			ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
							  CXD2880_IO_TGT_DMD,
							  set_ts_output_seq2,
							  ARRAY_SIZE(set_ts_output_seq2));
			if (ret)
				return ret;
		} else {
			ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
							  CXD2880_IO_TGT_DMD,
							  set_ts_output_seq3,
							  ARRAY_SIZE(set_ts_output_seq3));
			if (ret)
				return ret;

			ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
							  CXD2880_IO_TGT_SYS,
							  set_ts_output_seq4,
							  ARRAY_SIZE(set_ts_output_seq4));
			if (ret)
				return ret;
		}
		break;

	case CXD2880_TNRDMD_TSOUT_IF_SPI:
		break;

	case CXD2880_TNRDMD_TSOUT_IF_SDIO:
		break;

	default:
		return -EINVAL;
	}

	return 0;
}