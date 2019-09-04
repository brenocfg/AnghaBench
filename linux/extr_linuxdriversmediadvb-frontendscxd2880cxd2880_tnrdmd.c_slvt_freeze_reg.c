#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int ts_output_if; } ;
struct cxd2880_tnrdmd {TYPE_2__* io; TYPE_1__ create_param; } ;
struct TYPE_5__ {int (* read_regs ) (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ;int (* write_reg ) (TYPE_2__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
#define  CXD2880_TNRDMD_TSOUT_IF_SDIO 130 
#define  CXD2880_TNRDMD_TSOUT_IF_SPI 129 
#define  CXD2880_TNRDMD_TSOUT_IF_TS 128 
 int EINVAL ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 

int slvt_freeze_reg(struct cxd2880_tnrdmd *tnr_dmd)
{
	u8 data;
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	switch (tnr_dmd->create_param.ts_output_if) {
	case CXD2880_TNRDMD_TSOUT_IF_SPI:
	case CXD2880_TNRDMD_TSOUT_IF_SDIO:

		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, &data, 1);
		if (ret)
			return ret;

		break;
	case CXD2880_TNRDMD_TSOUT_IF_TS:
	default:
		break;
	}

	return tnr_dmd->io->write_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x01, 0x01);
}