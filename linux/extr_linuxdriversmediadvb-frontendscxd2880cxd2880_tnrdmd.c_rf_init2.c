#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cxd2880_tnrdmd {scalar_t__ chip_id; TYPE_1__* io; } ;
struct TYPE_5__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* write_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 scalar_t__ CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X ; 
 int EINVAL ; 
 int cxd2880_io_write_multi_regs (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rf_init2_seq1 ; 
 int /*<<< orphan*/  rf_init2_seq2 ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rf_init2(struct cxd2880_tnrdmd *tnr_dmd)
{
	u8 data[5] = { 0 };
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	if (ret)
		return ret;
	data[0] = 0x40;
	data[1] = 0x40;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xea, data, 2);
	if (ret)
		return ret;

	usleep_range(1000, 2000);

	data[0] = 0x00;
	if (tnr_dmd->chip_id == CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X)
		data[1] = 0x00;
	else
		data[1] = 0x01;
	data[2] = 0x01;
	data[3] = 0x03;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x30, data, 4);
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init2_seq1,
					  ARRAY_SIZE(rf_init2_seq1));
	if (ret)
		return ret;

	return cxd2880_io_write_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_DMD,
					   rf_init2_seq2,
					   ARRAY_SIZE(rf_init2_seq2));
}