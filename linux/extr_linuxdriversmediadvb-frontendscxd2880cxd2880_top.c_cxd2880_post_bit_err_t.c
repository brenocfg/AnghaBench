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
typedef  int u32 ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
struct TYPE_5__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int cxd2880_post_bit_err_t(struct cxd2880_tnrdmd *tnrdmd,
				  u32 *post_bit_err,
				  u32 *post_bit_count)
{
	u8 rdata[3];
	u32 bit_error = 0;
	u32 period_exp = 0;
	int ret;

	if (!tnrdmd || !post_bit_err || !post_bit_count)
		return -EINVAL;

	if (tnrdmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnrdmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnrdmd->sys != CXD2880_DTV_SYS_DVBT)
		return -EINVAL;

	ret = tnrdmd->io->write_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0d);
	if (ret)
		return ret;

	ret = tnrdmd->io->read_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x15, rdata, 3);
	if (ret)
		return ret;

	if ((rdata[0] & 0x40) == 0)
		return -EAGAIN;

	*post_bit_err = ((rdata[0] & 0x3f) << 16) | (rdata[1] << 8) | rdata[2];

	ret = tnrdmd->io->write_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x10);
	if (ret)
		return ret;

	ret = tnrdmd->io->read_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x60, rdata, 1);
	if (ret)
		return ret;

	period_exp = (rdata[0] & 0x1f);

	if (period_exp <= 11 && (bit_error > (1U << period_exp) * 204 * 8))
		return -EAGAIN;

	*post_bit_count = (1U << period_exp) * 204 * 8;

	return 0;
}