#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct cxd2880_tnrdmd {TYPE_1__* io; } ;
typedef  enum cxd2880_dtv_sys { ____Placeholder_cxd2880_dtv_sys } cxd2880_dtv_sys ;
typedef  enum cxd2880_dtv_bandwidth { ____Placeholder_cxd2880_dtv_bandwidth } cxd2880_dtv_bandwidth ;
struct TYPE_9__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* write_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CXD2880_DTV_BW_1_7_MHZ 134 
#define  CXD2880_DTV_BW_5_MHZ 133 
#define  CXD2880_DTV_BW_6_MHZ 132 
#define  CXD2880_DTV_BW_7_MHZ 131 
#define  CXD2880_DTV_BW_8_MHZ 130 
#define  CXD2880_DTV_SYS_DVBT 129 
#define  CXD2880_DTV_SYS_DVBT2 128 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 int EINVAL ; 
 int cxd2880_io_write_multi_regs (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub5 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub6 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub7 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  x_tune1_seq1 ; 
 int /*<<< orphan*/  x_tune1_seq2 ; 

__attribute__((used)) static int x_tune1(struct cxd2880_tnrdmd *tnr_dmd,
		   enum cxd2880_dtv_sys sys, u32 freq_khz,
		   enum cxd2880_dtv_bandwidth bandwidth,
		   u8 is_cable, int shift_frequency_khz)
{
	u8 data[11] = { 0 };
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  x_tune1_seq1,
					  ARRAY_SIZE(x_tune1_seq1));
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	if (ret)
		return ret;

	data[2] = 0x0e;
	data[4] = 0x03;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xe7, data, 5);
	if (ret)
		return ret;

	data[0] = 0x1f;
	data[1] = 0x80;
	data[2] = 0x18;
	data[3] = 0x00;
	data[4] = 0x07;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xe7, data, 5);
	if (ret)
		return ret;

	usleep_range(1000, 2000);

	data[0] = 0x72;
	data[1] = 0x81;
	data[3] = 0x1d;
	data[4] = 0x6f;
	data[5] = 0x7e;
	data[7] = 0x1c;
	switch (sys) {
	case CXD2880_DTV_SYS_DVBT:
		data[2] = 0x94;
		data[6] = 0x91;
		break;
	case CXD2880_DTV_SYS_DVBT2:
		data[2] = 0x96;
		data[6] = 0x93;
		break;
	default:
		return -EINVAL;
	}
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x44, data, 8);
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  x_tune1_seq2,
					  ARRAY_SIZE(x_tune1_seq2));
	if (ret)
		return ret;

	data[0] = 0x03;
	data[1] = 0xe2;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x1e, data, 2);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	if (ret)
		return ret;

	data[0] = is_cable ? 0x01 : 0x00;
	data[1] = 0x00;
	data[2] = 0x6b;
	data[3] = 0x4d;

	switch (bandwidth) {
	case CXD2880_DTV_BW_1_7_MHZ:
		data[4] = 0x03;
		break;
	case CXD2880_DTV_BW_5_MHZ:
	case CXD2880_DTV_BW_6_MHZ:
		data[4] = 0x00;
		break;
	case CXD2880_DTV_BW_7_MHZ:
		data[4] = 0x01;
		break;
	case CXD2880_DTV_BW_8_MHZ:
		data[4] = 0x02;
		break;
	default:
		return -EINVAL;
	}

	data[5] = 0x00;

	freq_khz += shift_frequency_khz;

	data[6] = (freq_khz >> 16) & 0x0f;
	data[7] = (freq_khz >> 8) & 0xff;
	data[8] = freq_khz & 0xff;
	data[9] = 0xff;
	data[10] = 0xfe;

	return tnr_dmd->io->write_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x52, data, 11);
}