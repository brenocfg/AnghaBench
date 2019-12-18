#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_txf_iter_data {int fifo; int fifo_size; } ;
struct TYPE_4__ {struct iwl_txf_iter_data txf_iter_data; } ;
struct iwl_fw_runtime {int /*<<< orphan*/  trans; TYPE_1__ dump; } ;
struct TYPE_6__ {scalar_t__ header_only; void* num_of_registers; } ;
struct iwl_fw_ini_region_cfg {TYPE_3__ fifos; void** start_addr; void* offset; } ;
struct iwl_fw_ini_error_dump_register {void* data; void* addr; } ;
struct TYPE_5__ {void* num_of_registers; void* fifo_num; } ;
struct iwl_fw_ini_error_dump_range {void* range_data_size; TYPE_2__ fifo_hdr; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int TXF_LARC_NUM ; 
 int TXF_READ_MODIFY_ADDR ; 
 int TXF_READ_MODIFY_DATA ; 
 int TXF_WR_PTR ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_ini_txf_iter (struct iwl_fw_runtime*,struct iwl_fw_ini_region_cfg*,int) ; 
 int iwl_read_prph_no_grab (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  iwl_write_prph_no_grab (int /*<<< orphan*/ ,int,int) ; 
 int le32_to_cpu (void*) ; 

__attribute__((used)) static int iwl_dump_ini_txf_iter(struct iwl_fw_runtime *fwrt,
				 struct iwl_fw_ini_region_cfg *reg,
				 void *range_ptr, int idx)
{
	struct iwl_fw_ini_error_dump_range *range = range_ptr;
	struct iwl_txf_iter_data *iter = &fwrt->dump.txf_iter_data;
	struct iwl_fw_ini_error_dump_register *reg_dump = (void *)range->data;
	u32 offs = le32_to_cpu(reg->offset), addr;
	u32 registers_size =
		le32_to_cpu(reg->fifos.num_of_registers) * sizeof(*reg_dump);
	__le32 *data;
	unsigned long flags;
	int i;

	if (!iwl_ini_txf_iter(fwrt, reg, idx))
		return -EIO;

	if (!iwl_trans_grab_nic_access(fwrt->trans, &flags))
		return -EBUSY;

	range->fifo_hdr.fifo_num = cpu_to_le32(iter->fifo);
	range->fifo_hdr.num_of_registers = reg->fifos.num_of_registers;
	range->range_data_size = cpu_to_le32(iter->fifo_size + registers_size);

	iwl_write_prph_no_grab(fwrt->trans, TXF_LARC_NUM + offs, iter->fifo);

	/*
	 * read txf registers. for each register, write to the dump the
	 * register address and its value
	 */
	for (i = 0; i < le32_to_cpu(reg->fifos.num_of_registers); i++) {
		addr = le32_to_cpu(reg->start_addr[i]) + offs;

		reg_dump->addr = cpu_to_le32(addr);
		reg_dump->data = cpu_to_le32(iwl_read_prph_no_grab(fwrt->trans,
								   addr));

		reg_dump++;
	}

	if (reg->fifos.header_only) {
		range->range_data_size = cpu_to_le32(registers_size);
		goto out;
	}

	/* Set the TXF_READ_MODIFY_ADDR to TXF_WR_PTR */
	iwl_write_prph_no_grab(fwrt->trans, TXF_READ_MODIFY_ADDR + offs,
			       TXF_WR_PTR + offs);

	/* Dummy-read to advance the read pointer to the head */
	iwl_read_prph_no_grab(fwrt->trans, TXF_READ_MODIFY_DATA + offs);

	/* Read FIFO */
	addr = TXF_READ_MODIFY_DATA + offs;
	data = (void *)reg_dump;
	for (i = 0; i < iter->fifo_size; i += sizeof(*data))
		*data++ = cpu_to_le32(iwl_read_prph_no_grab(fwrt->trans, addr));

out:
	iwl_trans_release_nic_access(fwrt->trans, &flags);

	return sizeof(*range) + le32_to_cpu(range->range_data_size);
}