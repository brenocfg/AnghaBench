#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cxd2880_tnrdmd {TYPE_1__* io; } ;
struct TYPE_3__ {int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 int EINVAL ; 
 int cxd2880_io_write_multi_regs (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  x_sleep2_seq1 ; 
 int /*<<< orphan*/  x_sleep2_seq2 ; 

__attribute__((used)) static int x_sleep2(struct cxd2880_tnrdmd *tnr_dmd)
{
	u8 data = 0;
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  x_sleep2_seq1,
					  ARRAY_SIZE(x_sleep2_seq1));
	if (ret)
		return ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xb2, &data, 1);
	if (ret)
		return ret;

	if ((data & 0x01) == 0x00)
		return -EINVAL;

	return cxd2880_io_write_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_SYS,
					   x_sleep2_seq2,
					   ARRAY_SIZE(x_sleep2_seq2));
}