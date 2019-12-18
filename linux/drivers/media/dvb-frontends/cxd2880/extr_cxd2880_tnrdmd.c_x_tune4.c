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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; TYPE_1__* diver_sub; TYPE_2__* io; } ;
struct TYPE_13__ {int (* write_reg ) (TYPE_2__*,int /*<<< orphan*/ ,int,int) ;int (* write_regs ) (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ;} ;
struct TYPE_12__ {TYPE_2__* io; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 int EINVAL ; 
 int cxd2880_io_write_multi_regs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub5 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub6 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub7 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub8 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub9 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  x_tune4_seq ; 

__attribute__((used)) static int x_tune4(struct cxd2880_tnrdmd *tnr_dmd)
{
	u8 data[2] = { 0 };
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->diver_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		return -EINVAL;

	ret = tnr_dmd->diver_sub->io->write_reg(tnr_dmd->diver_sub->io,
						CXD2880_IO_TGT_SYS,
						0x00, 0x00);
	if (ret)
		return ret;
	data[0] = 0x14;
	data[1] = 0x00;
	ret = tnr_dmd->diver_sub->io->write_regs(tnr_dmd->diver_sub->io,
						CXD2880_IO_TGT_SYS,
						0x55, data, 2);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	if (ret)
		return ret;
	data[0] = 0x0b;
	data[1] = 0xff;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x53, data, 2);
	if (ret)
		return ret;
	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x57, 0x01);
	if (ret)
		return ret;
	data[0] = 0x0b;
	data[1] = 0xff;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x55, data, 2);
	if (ret)
		return ret;

	ret = tnr_dmd->diver_sub->io->write_reg(tnr_dmd->diver_sub->io,
						CXD2880_IO_TGT_SYS,
						0x00, 0x00);
	if (ret)
		return ret;
	data[0] = 0x14;
	data[1] = 0x00;
	ret = tnr_dmd->diver_sub->io->write_regs(tnr_dmd->diver_sub->io,
						 CXD2880_IO_TGT_SYS,
						 0x53, data, 2);
	if (ret)
		return ret;
	ret = tnr_dmd->diver_sub->io->write_reg(tnr_dmd->diver_sub->io,
						CXD2880_IO_TGT_SYS,
						0x57, 0x02);
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  x_tune4_seq,
					  ARRAY_SIZE(x_tune4_seq));
	if (ret)
		return ret;

	return cxd2880_io_write_multi_regs(tnr_dmd->diver_sub->io,
					   CXD2880_IO_TGT_DMD,
					   x_tune4_seq,
					   ARRAY_SIZE(x_tune4_seq));
}