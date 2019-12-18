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
struct qla8044_minidump_entry_rdmdio {int addr_1; int addr_2; int value_1; int stride_1; int stride_2; scalar_t__ count; int mask; int value_2; } ;
struct qla8044_minidump_entry_hdr {int dummy; } ;

/* Variables and functions */
 int qla8044_ipmdio_rd_reg (struct scsi_qla_host*,int,int,int,int) ; 
 int qla8044_ipmdio_wr_reg (struct scsi_qla_host*,int,int,int,int,int) ; 
 int qla8044_poll_wait_ipmdio_bus_idle (struct scsi_qla_host*,int,int,int,int) ; 

__attribute__((used)) static uint32_t
qla8044_minidump_process_rdmdio(struct scsi_qla_host *vha,
	struct qla8044_minidump_entry_hdr *entry_hdr, uint32_t **d_ptr)
{
	int ret = 0;
	uint32_t addr1, addr2, value1, value2, data, selVal;
	uint8_t stride1, stride2;
	uint32_t addr3, addr4, addr5, addr6, addr7;
	uint16_t count, loop_cnt;
	uint32_t mask;
	uint32_t *data_ptr = *d_ptr;

	struct qla8044_minidump_entry_rdmdio *rdmdio;

	rdmdio = (struct qla8044_minidump_entry_rdmdio *) entry_hdr;

	addr1 = rdmdio->addr_1;
	addr2 = rdmdio->addr_2;
	value1 = rdmdio->value_1;
	stride1 = rdmdio->stride_1;
	stride2 = rdmdio->stride_2;
	count = rdmdio->count;

	mask = rdmdio->mask;
	value2 = rdmdio->value_2;

	addr3 = addr1 + stride1;

	for (loop_cnt = 0; loop_cnt < count; loop_cnt++) {
		ret = qla8044_poll_wait_ipmdio_bus_idle(vha, addr1, addr2,
		    addr3, mask);
		if (ret == -1)
			goto error;

		addr4 = addr2 - stride1;
		ret = qla8044_ipmdio_wr_reg(vha, addr1, addr3, mask, addr4,
		    value2);
		if (ret == -1)
			goto error;

		addr5 = addr2 - (2 * stride1);
		ret = qla8044_ipmdio_wr_reg(vha, addr1, addr3, mask, addr5,
		    value1);
		if (ret == -1)
			goto error;

		addr6 = addr2 - (3 * stride1);
		ret = qla8044_ipmdio_wr_reg(vha, addr1, addr3, mask,
		    addr6, 0x2);
		if (ret == -1)
			goto error;

		ret = qla8044_poll_wait_ipmdio_bus_idle(vha, addr1, addr2,
		    addr3, mask);
		if (ret == -1)
			goto error;

		addr7 = addr2 - (4 * stride1);
		data = qla8044_ipmdio_rd_reg(vha, addr1, addr3, mask, addr7);
		if (data == -1)
			goto error;

		selVal = (value2 << 18) | (value1 << 2) | 2;

		stride2 = rdmdio->stride_2;
		*data_ptr++ = selVal;
		*data_ptr++ = data;

		value1 = value1 + stride2;
		*d_ptr = data_ptr;
	}

	return 0;

error:
	return -1;
}