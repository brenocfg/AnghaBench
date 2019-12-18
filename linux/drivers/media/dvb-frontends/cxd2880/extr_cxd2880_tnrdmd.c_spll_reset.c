#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cxd2880_tnrdmd {TYPE_1__* io; } ;
typedef  enum cxd2880_tnrdmd_clockmode { ____Placeholder_cxd2880_tnrdmd_clockmode } cxd2880_tnrdmd_clockmode ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_8__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;int (* write_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
#define  CXD2880_TNRDMD_CLOCKMODE_A 130 
#define  CXD2880_TNRDMD_CLOCKMODE_B 129 
#define  CXD2880_TNRDMD_CLOCKMODE_C 128 
 int EINVAL ; 
 int cxd2880_io_write_multi_regs (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  spll_reset_seq1 ; 
 int /*<<< orphan*/  spll_reset_seq2 ; 
 int /*<<< orphan*/  spll_reset_seq3 ; 
 int /*<<< orphan*/  spll_reset_seq4 ; 
 int /*<<< orphan*/  spll_reset_seq5 ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub5 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub6 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int spll_reset(struct cxd2880_tnrdmd *tnr_dmd,
		      enum cxd2880_tnrdmd_clockmode clockmode)
{
	u8 data[4] = { 0 };
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  spll_reset_seq1,
					  ARRAY_SIZE(spll_reset_seq1));
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  spll_reset_seq2,
					  ARRAY_SIZE(spll_reset_seq2));
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  spll_reset_seq3,
					  ARRAY_SIZE(spll_reset_seq3));
	if (ret)
		return ret;

	switch (clockmode) {
	case CXD2880_TNRDMD_CLOCKMODE_A:
		data[0] = 0x00;
		break;

	case CXD2880_TNRDMD_CLOCKMODE_B:
		data[0] = 0x01;
		break;

	case CXD2880_TNRDMD_CLOCKMODE_C:
		data[0] = 0x02;
		break;

	default:
		return -EINVAL;
	}
	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x30, data[0]);
	if (ret)
		return ret;
	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x22, 0x00);
	if (ret)
		return ret;

	usleep_range(2000, 3000);

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	if (ret)
		return ret;
	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x10, data, 1);
	if (ret)
		return ret;
	if ((data[0] & 0x01) == 0x00)
		return -EINVAL;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  spll_reset_seq4,
					  ARRAY_SIZE(spll_reset_seq4));
	if (ret)
		return ret;

	usleep_range(1000, 2000);

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  spll_reset_seq5,
					  ARRAY_SIZE(spll_reset_seq5));
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	if (ret)
		return ret;

	memset(data, 0x00, sizeof(data));

	return tnr_dmd->io->write_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x26, data, 4);
}