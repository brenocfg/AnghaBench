#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_13__ {scalar_t__ stationary_use; } ;
struct cxd2880_tnrdmd {TYPE_2__* io; TYPE_1__ create_param; } ;
typedef  enum cxd2880_tnrdmd_clockmode { ____Placeholder_cxd2880_tnrdmd_clockmode } cxd2880_tnrdmd_clockmode ;
typedef  enum cxd2880_dtv_bandwidth { ____Placeholder_cxd2880_dtv_bandwidth } cxd2880_dtv_bandwidth ;
struct TYPE_14__ {int (* write_reg ) (TYPE_2__*,int /*<<< orphan*/ ,int,int) ;int (* write_regs ) (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ;int (* read_regs ) (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int CXD2880_DTV_BW_1_7_MHZ ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
#define  CXD2880_TNRDMD_CLOCKMODE_A 130 
#define  CXD2880_TNRDMD_CLOCKMODE_B 129 
#define  CXD2880_TNRDMD_CLOCKMODE_C 128 
 int EINVAL ; 
 scalar_t__ cxd2880_convert2s_complement (int,int) ; 
 int cxd2880_io_write_multi_regs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub10 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub4 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub5 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub6 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub7 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub8 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub9 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  x_tune2_seq1 ; 
 int /*<<< orphan*/  x_tune2_seq2 ; 
 int /*<<< orphan*/  x_tune2_seq3 ; 
 int /*<<< orphan*/  x_tune2_seq4 ; 
 int /*<<< orphan*/  x_tune2_seq5 ; 

__attribute__((used)) static int x_tune2(struct cxd2880_tnrdmd *tnr_dmd,
		   enum cxd2880_dtv_bandwidth bandwidth,
		   enum cxd2880_tnrdmd_clockmode clk_mode,
		   int shift_frequency_khz)
{
	u8 data[3] = { 0 };
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x11);
	if (ret)
		return ret;

	data[0] = 0x01;
	data[1] = 0x0e;
	data[2] = 0x01;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x2d, data, 3);
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  x_tune2_seq1,
					  ARRAY_SIZE(x_tune2_seq1));
	if (ret)
		return ret;

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x2c, data, 1);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x60, data[0]);
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  x_tune2_seq2,
					  ARRAY_SIZE(x_tune2_seq2));
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  x_tune2_seq3,
					  ARRAY_SIZE(x_tune2_seq3));
	if (ret)
		return ret;

	if (shift_frequency_khz != 0) {
		int shift_freq = 0;

		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0xe1);
		if (ret)
			return ret;

		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x60, data, 2);
		if (ret)
			return ret;

		shift_freq = shift_frequency_khz * 1000;

		switch (clk_mode) {
		case CXD2880_TNRDMD_CLOCKMODE_A:
		case CXD2880_TNRDMD_CLOCKMODE_C:
		default:
			if (shift_freq >= 0)
				shift_freq = (shift_freq + 183 / 2) / 183;
			else
				shift_freq = (shift_freq - 183 / 2) / 183;
			break;
		case CXD2880_TNRDMD_CLOCKMODE_B:
			if (shift_freq >= 0)
				shift_freq = (shift_freq + 178 / 2) / 178;
			else
				shift_freq = (shift_freq - 178 / 2) / 178;
			break;
		}

		shift_freq +=
		    cxd2880_convert2s_complement((data[0] << 8) | data[1], 16);

		if (shift_freq > 32767)
			shift_freq = 32767;
		else if (shift_freq < -32768)
			shift_freq = -32768;

		data[0] = (shift_freq >> 8) & 0xff;
		data[1] = shift_freq & 0xff;

		ret = tnr_dmd->io->write_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 2);
		if (ret)
			return ret;

		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x69, data, 1);
		if (ret)
			return ret;

		shift_freq = -shift_frequency_khz;

		if (bandwidth == CXD2880_DTV_BW_1_7_MHZ) {
			switch (clk_mode) {
			case CXD2880_TNRDMD_CLOCKMODE_A:
			case CXD2880_TNRDMD_CLOCKMODE_C:
			default:
				if (shift_freq >= 0)
					shift_freq =
					    (shift_freq * 1000 +
					     17578 / 2) / 17578;
				else
					shift_freq =
					    (shift_freq * 1000 -
					     17578 / 2) / 17578;
				break;
			case CXD2880_TNRDMD_CLOCKMODE_B:
				if (shift_freq >= 0)
					shift_freq =
					    (shift_freq * 1000 +
					     17090 / 2) / 17090;
				else
					shift_freq =
					    (shift_freq * 1000 -
					     17090 / 2) / 17090;
				break;
			}
		} else {
			switch (clk_mode) {
			case CXD2880_TNRDMD_CLOCKMODE_A:
			case CXD2880_TNRDMD_CLOCKMODE_C:
			default:
				if (shift_freq >= 0)
					shift_freq =
					    (shift_freq * 1000 +
					     35156 / 2) / 35156;
				else
					shift_freq =
					    (shift_freq * 1000 -
					     35156 / 2) / 35156;
				break;
			case CXD2880_TNRDMD_CLOCKMODE_B:
				if (shift_freq >= 0)
					shift_freq =
					    (shift_freq * 1000 +
					     34180 / 2) / 34180;
				else
					shift_freq =
					    (shift_freq * 1000 -
					     34180 / 2) / 34180;
				break;
			}
		}

		shift_freq += cxd2880_convert2s_complement(data[0], 8);

		if (shift_freq > 127)
			shift_freq = 127;
		else if (shift_freq < -128)
			shift_freq = -128;

		data[0] = shift_freq & 0xff;

		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x69, data[0]);
		if (ret)
			return ret;
	}

	if (tnr_dmd->create_param.stationary_use) {
		ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
						  CXD2880_IO_TGT_DMD,
						  x_tune2_seq4,
						  ARRAY_SIZE(x_tune2_seq4));
		if (ret)
			return ret;
	}

	return cxd2880_io_write_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_DMD,
					   x_tune2_seq5,
					   ARRAY_SIZE(x_tune2_seq5));
}