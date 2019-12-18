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
typedef  int uint32_t ;
struct scsi_qla_host {TYPE_1__* isp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rd_reg_indirect ) (struct scsi_qla_host*,int,int*) ;int /*<<< orphan*/  (* wr_reg_indirect ) (struct scsi_qla_host*,int,int) ;} ;

/* Variables and functions */
 int QLA_SUCCESS ; 
 int ql4_84xx_poll_wait_for_ready (struct scsi_qla_host*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*,int,int*) ; 

__attribute__((used)) static uint32_t ql4_84xx_ipmdio_rd_reg(struct scsi_qla_host *ha, uint32_t addr1,
				uint32_t addr3, uint32_t mask, uint32_t addr,
				uint32_t *data_ptr)
{
	int rval = QLA_SUCCESS;
	uint32_t temp;
	uint32_t data;

	rval = ql4_84xx_poll_wait_for_ready(ha, addr1, mask);
	if (rval)
		goto exit_ipmdio_rd_reg;

	temp = (0x40000000 | addr);
	ha->isp_ops->wr_reg_indirect(ha, addr1, temp);

	rval = ql4_84xx_poll_wait_for_ready(ha, addr1, mask);
	if (rval)
		goto exit_ipmdio_rd_reg;

	ha->isp_ops->rd_reg_indirect(ha, addr3, &data);
	*data_ptr = data;

exit_ipmdio_rd_reg:
	return rval;
}