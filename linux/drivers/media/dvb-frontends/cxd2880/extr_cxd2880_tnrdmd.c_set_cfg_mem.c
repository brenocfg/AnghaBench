#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct cxd2880_tnrdmd {size_t cfg_mem_last_entry; TYPE_1__* cfg_mem; } ;
typedef  enum cxd2880_io_tgt { ____Placeholder_cxd2880_io_tgt } cxd2880_io_tgt ;
struct TYPE_2__ {int tgt; size_t bank; size_t address; size_t value; size_t bit_mask; } ;

/* Variables and functions */
 scalar_t__ CXD2880_TNRDMD_MAX_CFG_MEM_COUNT ; 
 int EINVAL ; 
 int ENOMEM ; 

__attribute__((used)) static int set_cfg_mem(struct cxd2880_tnrdmd *tnr_dmd,
		       enum cxd2880_io_tgt tgt,
		       u8 bank, u8 address, u8 value, u8 bit_mask)
{
	u8 i;
	u8 value_stored = 0;

	if (!tnr_dmd)
		return -EINVAL;

	for (i = 0; i < tnr_dmd->cfg_mem_last_entry; i++) {
		if (value_stored == 0 &&
		    tnr_dmd->cfg_mem[i].tgt == tgt &&
		    tnr_dmd->cfg_mem[i].bank == bank &&
		    tnr_dmd->cfg_mem[i].address == address) {
			tnr_dmd->cfg_mem[i].value &= ~bit_mask;
			tnr_dmd->cfg_mem[i].value |= (value & bit_mask);

			tnr_dmd->cfg_mem[i].bit_mask |= bit_mask;

			value_stored = 1;
		}
	}

	if (value_stored)
		return 0;

	if (tnr_dmd->cfg_mem_last_entry < CXD2880_TNRDMD_MAX_CFG_MEM_COUNT) {
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].tgt = tgt;
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].bank = bank;
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].address = address;
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].value = (value & bit_mask);
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].bit_mask = bit_mask;
		tnr_dmd->cfg_mem_last_entry++;
	} else {
		return -ENOMEM;
	}

	return 0;
}