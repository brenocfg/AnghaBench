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
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {int dummy; } ;
struct qla8044_minidump_entry_hdr {int dummy; } ;
struct TYPE_6__ {scalar_t__ init_tag_value; scalar_t__ tag_value_stride; } ;
struct TYPE_5__ {scalar_t__ read_addr_cnt; scalar_t__ read_addr_stride; } ;
struct TYPE_4__ {scalar_t__ write_value; } ;
struct qla8044_minidump_entry_cache {scalar_t__ op_count; scalar_t__ read_addr; scalar_t__ control_addr; scalar_t__ tag_reg_addr; TYPE_3__ addr_ctrl; TYPE_2__ read_ctrl; TYPE_1__ cache_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla8044_rd_reg_indirect (struct scsi_qla_host*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  qla8044_wr_reg_indirect (struct scsi_qla_host*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
qla8044_minidump_process_l1cache(struct scsi_qla_host *vha,
	struct qla8044_minidump_entry_hdr *entry_hdr, uint32_t **d_ptr)
{
	uint32_t addr, r_addr, c_addr, t_r_addr;
	uint32_t i, k, loop_count, t_value, r_cnt, r_value;
	uint32_t c_value_w;
	struct qla8044_minidump_entry_cache *cache_hdr;
	uint32_t *data_ptr = *d_ptr;

	cache_hdr = (struct qla8044_minidump_entry_cache *)entry_hdr;
	loop_count = cache_hdr->op_count;
	r_addr = cache_hdr->read_addr;
	c_addr = cache_hdr->control_addr;
	c_value_w = cache_hdr->cache_ctrl.write_value;

	t_r_addr = cache_hdr->tag_reg_addr;
	t_value = cache_hdr->addr_ctrl.init_tag_value;
	r_cnt = cache_hdr->read_ctrl.read_addr_cnt;

	for (i = 0; i < loop_count; i++) {
		qla8044_wr_reg_indirect(vha, t_r_addr, t_value);
		qla8044_wr_reg_indirect(vha, c_addr, c_value_w);
		addr = r_addr;
		for (k = 0; k < r_cnt; k++) {
			qla8044_rd_reg_indirect(vha, addr, &r_value);
			*data_ptr++ = r_value;
			addr += cache_hdr->read_ctrl.read_addr_stride;
		}
		t_value += cache_hdr->addr_ctrl.tag_value_stride;
	}
	*d_ptr = data_ptr;
}