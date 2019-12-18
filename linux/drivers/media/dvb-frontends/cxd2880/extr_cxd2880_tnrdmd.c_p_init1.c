#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_12__ {int ts_output_if; scalar_t__ en_internal_ldo; } ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; int chip_id; TYPE_2__* io; TYPE_1__ create_param; } ;
struct TYPE_13__ {int (* write_reg ) (TYPE_2__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
#define  CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X 132 
#define  CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_11 131 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SINGLE ; 
#define  CXD2880_TNRDMD_TSOUT_IF_SDIO 130 
#define  CXD2880_TNRDMD_TSOUT_IF_SPI 129 
#define  CXD2880_TNRDMD_TSOUT_IF_TS 128 
 int EINVAL ; 
 int ENOTTY ; 
 int cxd2880_io_write_multi_regs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_init1_seq ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub3 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub5 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub6 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub7 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub8 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub9 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int p_init1(struct cxd2880_tnrdmd *tnr_dmd)
{
	u8 data = 0;
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE ||
	    tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		switch (tnr_dmd->create_param.ts_output_if) {
		case CXD2880_TNRDMD_TSOUT_IF_TS:
			data = 0x00;
			break;
		case CXD2880_TNRDMD_TSOUT_IF_SPI:
			data = 0x01;
			break;
		case CXD2880_TNRDMD_TSOUT_IF_SDIO:
			data = 0x02;
			break;
		default:
			return -EINVAL;
		}
		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x10, data);
		if (ret)
			return ret;
	}

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  p_init1_seq,
					  ARRAY_SIZE(p_init1_seq));
	if (ret)
		return ret;

	switch (tnr_dmd->chip_id) {
	case CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X:
		data = 0x1a;
		break;
	case CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_11:
		data = 0x16;
		break;
	default:
		return -ENOTTY;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x10, data);
	if (ret)
		return ret;

	if (tnr_dmd->create_param.en_internal_ldo)
		data = 0x01;
	else
		data = 0x00;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x11, data);
	if (ret)
		return ret;
	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x13, data);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	if (ret)
		return ret;
	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x12, data);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	if (ret)
		return ret;

	switch (tnr_dmd->chip_id) {
	case CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X:
		data = 0x01;
		break;
	case CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_11:
		data = 0x00;
		break;
	default:
		return -ENOTTY;
	}

	return tnr_dmd->io->write_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x69, data);
}