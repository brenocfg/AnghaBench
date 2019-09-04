#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct cxd2880_tnrdmd {size_t cfg_mem_last_entry; TYPE_1__* cfg_mem; TYPE_2__* io; } ;
struct TYPE_5__ {int (* write_reg ) (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  bit_mask; int /*<<< orphan*/  value; int /*<<< orphan*/  address; int /*<<< orphan*/  tgt; int /*<<< orphan*/  bank; } ;

/* Variables and functions */
 int EINVAL ; 
 int cxd2880_io_set_reg_bits (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_cfg_mem(struct cxd2880_tnrdmd *tnr_dmd)
{
	int ret;
	u8 i;

	if (!tnr_dmd)
		return -EINVAL;

	for (i = 0; i < tnr_dmd->cfg_mem_last_entry; i++) {
		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     tnr_dmd->cfg_mem[i].tgt,
					     0x00, tnr_dmd->cfg_mem[i].bank);
		if (ret)
			return ret;

		ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
					      tnr_dmd->cfg_mem[i].tgt,
					      tnr_dmd->cfg_mem[i].address,
					      tnr_dmd->cfg_mem[i].value,
					      tnr_dmd->cfg_mem[i].bit_mask);
		if (ret)
			return ret;
	}

	return 0;
}