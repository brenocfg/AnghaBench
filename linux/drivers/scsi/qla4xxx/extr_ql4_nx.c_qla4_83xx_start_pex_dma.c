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
struct qla4_83xx_minidump_entry_rdmem_pex_dma {int /*<<< orphan*/  start_dma_cmd; int /*<<< orphan*/  desc_card_addr; } ;
struct TYPE_2__ {int (* wr_reg_indirect ) (struct scsi_qla_host*,scalar_t__,int /*<<< orphan*/ ) ;int (* rd_reg_indirect ) (struct scsi_qla_host*,scalar_t__,int*) ;} ;

/* Variables and functions */
 int BIT_1 ; 
 scalar_t__ QLA83XX_PEX_DMA_BASE_ADDRESS ; 
 scalar_t__ QLA83XX_PEX_DMA_CMD_ADDR_HIGH ; 
 scalar_t__ QLA83XX_PEX_DMA_CMD_ADDR_LOW ; 
 scalar_t__ QLA83XX_PEX_DMA_CMD_STS_AND_CNTRL ; 
 size_t QLA83XX_PEX_DMA_ENGINE_INDEX ; 
 int QLA83XX_PEX_DMA_MAX_WAIT ; 
 int QLA83XX_PEX_DMA_NUM_OFFSET ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int stub1 (struct scsi_qla_host*,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub2 (struct scsi_qla_host*,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub3 (struct scsi_qla_host*,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub4 (struct scsi_qla_host*,scalar_t__,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int qla4_83xx_start_pex_dma(struct scsi_qla_host *ha,
			   struct qla4_83xx_minidump_entry_rdmem_pex_dma *m_hdr)
{
	int rval = QLA_SUCCESS, wait = 0;
	uint32_t dma_eng_num = 0, cmd_sts_and_cntrl = 0;
	uint64_t dma_base_addr = 0;
	struct qla4_8xxx_minidump_template_hdr *tmplt_hdr = NULL;

	tmplt_hdr = (struct qla4_8xxx_minidump_template_hdr *)
							ha->fw_dump_tmplt_hdr;
	dma_eng_num =
		tmplt_hdr->saved_state_array[QLA83XX_PEX_DMA_ENGINE_INDEX];
	dma_base_addr = QLA83XX_PEX_DMA_BASE_ADDRESS +
				(dma_eng_num * QLA83XX_PEX_DMA_NUM_OFFSET);

	rval = ha->isp_ops->wr_reg_indirect(ha,
				dma_base_addr + QLA83XX_PEX_DMA_CMD_ADDR_LOW,
				m_hdr->desc_card_addr);
	if (rval)
		goto error_exit;

	rval = ha->isp_ops->wr_reg_indirect(ha,
			      dma_base_addr + QLA83XX_PEX_DMA_CMD_ADDR_HIGH, 0);
	if (rval)
		goto error_exit;

	rval = ha->isp_ops->wr_reg_indirect(ha,
			      dma_base_addr + QLA83XX_PEX_DMA_CMD_STS_AND_CNTRL,
			      m_hdr->start_dma_cmd);
	if (rval)
		goto error_exit;

	/* Wait for dma operation to complete. */
	for (wait = 0; wait < QLA83XX_PEX_DMA_MAX_WAIT; wait++) {
		rval = ha->isp_ops->rd_reg_indirect(ha,
			    (dma_base_addr + QLA83XX_PEX_DMA_CMD_STS_AND_CNTRL),
			    &cmd_sts_and_cntrl);
		if (rval)
			goto error_exit;

		if ((cmd_sts_and_cntrl & BIT_1) == 0)
			break;
		else
			udelay(10);
	}

	/* Wait a max of 100 ms, otherwise fallback to rdmem entry read */
	if (wait >= QLA83XX_PEX_DMA_MAX_WAIT) {
		rval = QLA_ERROR;
		goto error_exit;
	}

error_exit:
	return rval;
}