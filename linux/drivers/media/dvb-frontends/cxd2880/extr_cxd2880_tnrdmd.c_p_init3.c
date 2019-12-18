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
struct cxd2880_tnrdmd {int diver_mode; TYPE_1__* io; } ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* write_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
#define  CXD2880_TNRDMD_DIVERMODE_MAIN 130 
#define  CXD2880_TNRDMD_DIVERMODE_SINGLE 129 
#define  CXD2880_TNRDMD_DIVERMODE_SUB 128 
 int EINVAL ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int p_init3(struct cxd2880_tnrdmd *tnr_dmd)
{
	u8 data[2] = { 0 };
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	if (ret)
		return ret;

	switch (tnr_dmd->diver_mode) {
	case CXD2880_TNRDMD_DIVERMODE_SINGLE:
		data[0] = 0x00;
		break;
	case CXD2880_TNRDMD_DIVERMODE_MAIN:
		data[0] = 0x03;
		break;
	case CXD2880_TNRDMD_DIVERMODE_SUB:
		data[0] = 0x02;
		break;
	default:
		return -EINVAL;
	}

	data[1] = 0x01;

	return tnr_dmd->io->write_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x1f, data, 2);
}