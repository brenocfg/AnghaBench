#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct scsi_qla_host {int dummy; } ;
struct qla8xxx_minidump_entry_hdr {int dummy; } ;
struct qla8044_minidump_entry_rdmdio {int /*<<< orphan*/  stride_2; int /*<<< orphan*/  value_2; int /*<<< orphan*/  mask; int /*<<< orphan*/  poll; int /*<<< orphan*/  count; int /*<<< orphan*/  stride_1; int /*<<< orphan*/  value_1; int /*<<< orphan*/  addr_2; int /*<<< orphan*/  addr_1; } ;

/* Variables and functions */
 int QLA_SUCCESS ; 
 void* cpu_to_le32 (int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ql4_84xx_ipmdio_rd_reg (struct scsi_qla_host*,int,int,int,int,int*) ; 
 int ql4_84xx_ipmdio_wr_reg (struct scsi_qla_host*,int,int,int,int,int) ; 
 int ql4_84xx_poll_wait_ipmdio_bus_idle (struct scsi_qla_host*,int,int,int,int) ; 

__attribute__((used)) static uint32_t qla4_84xx_minidump_process_rdmdio(struct scsi_qla_host *ha,
				struct qla8xxx_minidump_entry_hdr *entry_hdr,
				uint32_t **d_ptr)
{
	int rval = QLA_SUCCESS;
	uint32_t addr1, addr2, value1, value2, data, selval;
	uint8_t stride1, stride2;
	uint32_t addr3, addr4, addr5, addr6, addr7;
	uint16_t count, loop_cnt;
	uint32_t poll, mask;
	uint32_t *data_ptr = *d_ptr;
	struct qla8044_minidump_entry_rdmdio *rdmdio;

	rdmdio = (struct qla8044_minidump_entry_rdmdio *)entry_hdr;
	addr1 = le32_to_cpu(rdmdio->addr_1);
	addr2 = le32_to_cpu(rdmdio->addr_2);
	value1 = le32_to_cpu(rdmdio->value_1);
	stride1 = le32_to_cpu(rdmdio->stride_1);
	stride2 = le32_to_cpu(rdmdio->stride_2);
	count = le32_to_cpu(rdmdio->count);

	poll = le32_to_cpu(rdmdio->poll);
	mask = le32_to_cpu(rdmdio->mask);
	value2 = le32_to_cpu(rdmdio->value_2);

	addr3 = addr1 + stride1;

	for (loop_cnt = 0; loop_cnt < count; loop_cnt++) {
		rval = ql4_84xx_poll_wait_ipmdio_bus_idle(ha, addr1, addr2,
							 addr3, mask);
		if (rval)
			goto exit_process_rdmdio;

		addr4 = addr2 - stride1;
		rval = ql4_84xx_ipmdio_wr_reg(ha, addr1, addr3, mask, addr4,
					     value2);
		if (rval)
			goto exit_process_rdmdio;

		addr5 = addr2 - (2 * stride1);
		rval = ql4_84xx_ipmdio_wr_reg(ha, addr1, addr3, mask, addr5,
					     value1);
		if (rval)
			goto exit_process_rdmdio;

		addr6 = addr2 - (3 * stride1);
		rval = ql4_84xx_ipmdio_wr_reg(ha, addr1, addr3, mask,
					     addr6, 0x2);
		if (rval)
			goto exit_process_rdmdio;

		rval = ql4_84xx_poll_wait_ipmdio_bus_idle(ha, addr1, addr2,
							 addr3, mask);
		if (rval)
			goto exit_process_rdmdio;

		addr7 = addr2 - (4 * stride1);
		rval = ql4_84xx_ipmdio_rd_reg(ha, addr1, addr3,
						      mask, addr7, &data);
		if (rval)
			goto exit_process_rdmdio;

		selval = (value2 << 18) | (value1 << 2) | 2;

		stride2 = le32_to_cpu(rdmdio->stride_2);
		*data_ptr++ = cpu_to_le32(selval);
		*data_ptr++ = cpu_to_le32(data);

		value1 = value1 + stride2;
		*d_ptr = data_ptr;
	}

exit_process_rdmdio:
	return rval;
}