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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct scsi_qla_host {TYPE_1__* isp_ops; scalar_t__ fw_dump_tmplt_hdr; } ;
struct qla4_8xxx_minidump_template_hdr {int* saved_state_array; } ;
struct TYPE_2__ {int (* rd_reg_indirect ) (struct scsi_qla_host*,scalar_t__,int*) ;} ;

/* Variables and functions */
 int BIT_31 ; 
 scalar_t__ QLA83XX_PEX_DMA_BASE_ADDRESS ; 
 scalar_t__ QLA83XX_PEX_DMA_CMD_STS_AND_CNTRL ; 
 size_t QLA83XX_PEX_DMA_ENGINE_INDEX ; 
 int QLA83XX_PEX_DMA_NUM_OFFSET ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int stub1 (struct scsi_qla_host*,scalar_t__,int*) ; 

__attribute__((used)) static int qla4_83xx_check_dma_engine_state(struct scsi_qla_host *ha)
{
	int rval = QLA_SUCCESS;
	uint32_t dma_eng_num = 0, cmd_sts_and_cntrl = 0;
	uint64_t dma_base_addr = 0;
	struct qla4_8xxx_minidump_template_hdr *tmplt_hdr = NULL;

	tmplt_hdr = (struct qla4_8xxx_minidump_template_hdr *)
							ha->fw_dump_tmplt_hdr;
	dma_eng_num =
		tmplt_hdr->saved_state_array[QLA83XX_PEX_DMA_ENGINE_INDEX];
	dma_base_addr = QLA83XX_PEX_DMA_BASE_ADDRESS +
				(dma_eng_num * QLA83XX_PEX_DMA_NUM_OFFSET);

	/* Read the pex-dma's command-status-and-control register. */
	rval = ha->isp_ops->rd_reg_indirect(ha,
			(dma_base_addr + QLA83XX_PEX_DMA_CMD_STS_AND_CNTRL),
			&cmd_sts_and_cntrl);

	if (rval)
		return QLA_ERROR;

	/* Check if requested pex-dma engine is available. */
	if (cmd_sts_and_cntrl & BIT_31)
		return QLA_SUCCESS;
	else
		return QLA_ERROR;
}