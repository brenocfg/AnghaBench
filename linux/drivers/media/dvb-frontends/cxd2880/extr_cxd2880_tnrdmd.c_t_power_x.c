#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cxd2880_tnrdmd {TYPE_1__* io; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_12__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;int (* write_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 int EINVAL ; 
 int cxd2880_io_write_multi_regs (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub10 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub5 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub6 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub7 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub8 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub9 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t_power_x_seq1 ; 
 int /*<<< orphan*/  t_power_x_seq2 ; 
 int /*<<< orphan*/  t_power_x_seq3 ; 
 int /*<<< orphan*/  t_power_x_seq4 ; 
 int /*<<< orphan*/  t_power_x_seq5 ; 
 int /*<<< orphan*/  t_power_x_seq6 ; 
 int /*<<< orphan*/  t_power_x_seq7 ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int t_power_x(struct cxd2880_tnrdmd *tnr_dmd, u8 on)
{
	u8 data[3] = { 0 };
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  t_power_x_seq1,
					  ARRAY_SIZE(t_power_x_seq1));
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  t_power_x_seq2,
					  ARRAY_SIZE(t_power_x_seq2));
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  t_power_x_seq3,
					  ARRAY_SIZE(t_power_x_seq3));
	if (ret)
		return ret;

	if (on) {
		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x2b, 0x01);
		if (ret)
			return ret;

		usleep_range(1000, 2000);

		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x00, 0x0a);
		if (ret)
			return ret;
		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x12, data, 1);
		if (ret)
			return ret;
		if ((data[0] & 0x01) == 0)
			return -EINVAL;

		ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
						  CXD2880_IO_TGT_SYS,
						  t_power_x_seq4,
						  ARRAY_SIZE(t_power_x_seq4));
		if (ret)
			return ret;
	} else {
		data[0] = 0x03;
		data[1] = 0x00;
		ret = tnr_dmd->io->write_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_SYS,
					      0x2a, data, 2);
		if (ret)
			return ret;

		usleep_range(1000, 2000);

		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x00, 0x0a);
		if (ret)
			return ret;
		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x13, data, 1);
		if (ret)
			return ret;
		if ((data[0] & 0x01) == 0)
			return -EINVAL;
	}

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  t_power_x_seq5,
					  ARRAY_SIZE(t_power_x_seq5));
	if (ret)
		return ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	if (ret)
		return ret;
	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x11, data, 1);
	if (ret)
		return ret;
	if ((data[0] & 0x01) == 0)
		return -EINVAL;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  t_power_x_seq6,
					  ARRAY_SIZE(t_power_x_seq6));
	if (ret)
		return ret;

	usleep_range(1000, 2000);

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  t_power_x_seq7,
					  ARRAY_SIZE(t_power_x_seq7));
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
				       0x27, data, 3);
}