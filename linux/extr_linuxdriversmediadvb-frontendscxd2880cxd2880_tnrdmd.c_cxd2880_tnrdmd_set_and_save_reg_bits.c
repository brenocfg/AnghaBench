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
typedef  int /*<<< orphan*/  u8 ;
struct cxd2880_tnrdmd {scalar_t__ state; TYPE_1__* io; } ;
typedef  enum cxd2880_io_tgt { ____Placeholder_cxd2880_io_tgt } cxd2880_io_tgt ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 int EINVAL ; 
 int cxd2880_io_set_reg_bits (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_cfg_mem (struct cxd2880_tnrdmd*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

int cxd2880_tnrdmd_set_and_save_reg_bits(struct cxd2880_tnrdmd
					 *tnr_dmd,
					 enum cxd2880_io_tgt tgt,
					 u8 bank, u8 address,
					 u8 value, u8 bit_mask)
{
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io, tgt, 0x00, bank);
	if (ret)
		return ret;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      tgt, address, value, bit_mask);
	if (ret)
		return ret;

	return set_cfg_mem(tnr_dmd, tgt, bank, address, value, bit_mask);
}