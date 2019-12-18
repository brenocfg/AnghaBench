#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct sli4_sge {int word2; void* sge_len; void* addr_lo; void* addr_hi; } ;
struct scsi_cmnd {int /*<<< orphan*/  request; } ;
struct lpfc_sli4_hdw_queue {int /*<<< orphan*/  empty_io_bufs; } ;
struct lpfc_nodelist {int /*<<< orphan*/  cmd_pending; } ;
struct TYPE_11__ {int bdeSize; int addrLow; int addrHigh; int /*<<< orphan*/  bdeFlags; scalar_t__ ulpIoTag32; } ;
struct TYPE_12__ {TYPE_4__ bdl; } ;
struct TYPE_13__ {TYPE_5__ fcpi64; } ;
struct TYPE_14__ {int ulpBdeCount; int ulpLe; int /*<<< orphan*/  ulpClass; TYPE_6__ un; } ;
struct TYPE_10__ {TYPE_7__ iocb; int /*<<< orphan*/  iocb_flag; } ;
struct lpfc_io_buf {size_t cpu; int /*<<< orphan*/  flags; TYPE_3__ cur_iocbq; scalar_t__ dma_sgl; int /*<<< orphan*/  fcp_rsp; int /*<<< orphan*/  fcp_cmnd; scalar_t__ prot_data_type; int /*<<< orphan*/ * waitq; int /*<<< orphan*/  start_time; scalar_t__ timeout; scalar_t__ seg_cnt; scalar_t__ prot_seg_cnt; } ;
struct TYPE_9__ {struct lpfc_sli4_hdw_queue* hdwq; TYPE_1__* cpu_map; } ;
struct lpfc_hba {scalar_t__ cfg_fcp_io_sched; TYPE_2__ sli4_hba; int /*<<< orphan*/  cfg_xri_rebalancing; } ;
struct fcp_rsp {int dummy; } ;
struct fcp_cmnd {int dummy; } ;
struct fcp_cmd_rsp_buf {scalar_t__ fcp_cmd_rsp_dma_handle; int /*<<< orphan*/  fcp_rsp; int /*<<< orphan*/  fcp_cmnd; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_8__ {size_t hdwq; } ;
typedef  TYPE_7__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFF_TYPE_BDE_64 ; 
 int /*<<< orphan*/  CLASS3 ; 
 scalar_t__ LPFC_FCP_SCHED_BY_HDWQ ; 
 int /*<<< orphan*/  LPFC_IO_FCP ; 
 int /*<<< orphan*/  LPFC_SBUF_BUMP_QDEPTH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct sli4_sge*,int) ; 
 int blk_mq_unique_tag (int /*<<< orphan*/ ) ; 
 size_t blk_mq_unique_tag_to_hwq (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  jiffies ; 
 void* le32_to_cpu (int) ; 
 struct fcp_cmd_rsp_buf* lpfc_get_cmd_rsp_buf_per_hdwq (struct lpfc_hba*,struct lpfc_io_buf*) ; 
 struct lpfc_io_buf* lpfc_get_io_buf (struct lpfc_hba*,struct lpfc_nodelist*,size_t,int) ; 
 scalar_t__ lpfc_ndlp_check_qdepth (struct lpfc_hba*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_sli4_sge_last ; 
 int putPaddrHigh (scalar_t__) ; 
 int putPaddrLow (scalar_t__) ; 
 size_t raw_smp_processor_id () ; 

__attribute__((used)) static struct lpfc_io_buf *
lpfc_get_scsi_buf_s4(struct lpfc_hba *phba, struct lpfc_nodelist *ndlp,
		     struct scsi_cmnd *cmnd)
{
	struct lpfc_io_buf *lpfc_cmd;
	struct lpfc_sli4_hdw_queue *qp;
	struct sli4_sge *sgl;
	IOCB_t *iocb;
	dma_addr_t pdma_phys_fcp_rsp;
	dma_addr_t pdma_phys_fcp_cmd;
	uint32_t cpu, idx;
	int tag;
	struct fcp_cmd_rsp_buf *tmp = NULL;

	cpu = raw_smp_processor_id();
	if (cmnd && phba->cfg_fcp_io_sched == LPFC_FCP_SCHED_BY_HDWQ) {
		tag = blk_mq_unique_tag(cmnd->request);
		idx = blk_mq_unique_tag_to_hwq(tag);
	} else {
		idx = phba->sli4_hba.cpu_map[cpu].hdwq;
	}

	lpfc_cmd = lpfc_get_io_buf(phba, ndlp, idx,
				   !phba->cfg_xri_rebalancing);
	if (!lpfc_cmd) {
		qp = &phba->sli4_hba.hdwq[idx];
		qp->empty_io_bufs++;
		return NULL;
	}

	/* Setup key fields in buffer that may have been changed
	 * if other protocols used this buffer.
	 */
	lpfc_cmd->cur_iocbq.iocb_flag = LPFC_IO_FCP;
	lpfc_cmd->prot_seg_cnt = 0;
	lpfc_cmd->seg_cnt = 0;
	lpfc_cmd->timeout = 0;
	lpfc_cmd->flags = 0;
	lpfc_cmd->start_time = jiffies;
	lpfc_cmd->waitq = NULL;
	lpfc_cmd->cpu = cpu;
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	lpfc_cmd->prot_data_type = 0;
#endif
	tmp = lpfc_get_cmd_rsp_buf_per_hdwq(phba, lpfc_cmd);
	if (!tmp)
		return NULL;

	lpfc_cmd->fcp_cmnd = tmp->fcp_cmnd;
	lpfc_cmd->fcp_rsp = tmp->fcp_rsp;

	/*
	 * The first two SGEs are the FCP_CMD and FCP_RSP.
	 * The balance are sg list bdes. Initialize the
	 * first two and leave the rest for queuecommand.
	 */
	sgl = (struct sli4_sge *)lpfc_cmd->dma_sgl;
	pdma_phys_fcp_cmd = tmp->fcp_cmd_rsp_dma_handle;
	sgl->addr_hi = cpu_to_le32(putPaddrHigh(pdma_phys_fcp_cmd));
	sgl->addr_lo = cpu_to_le32(putPaddrLow(pdma_phys_fcp_cmd));
	sgl->word2 = le32_to_cpu(sgl->word2);
	bf_set(lpfc_sli4_sge_last, sgl, 0);
	sgl->word2 = cpu_to_le32(sgl->word2);
	sgl->sge_len = cpu_to_le32(sizeof(struct fcp_cmnd));
	sgl++;

	/* Setup the physical region for the FCP RSP */
	pdma_phys_fcp_rsp = pdma_phys_fcp_cmd + sizeof(struct fcp_cmnd);
	sgl->addr_hi = cpu_to_le32(putPaddrHigh(pdma_phys_fcp_rsp));
	sgl->addr_lo = cpu_to_le32(putPaddrLow(pdma_phys_fcp_rsp));
	sgl->word2 = le32_to_cpu(sgl->word2);
	bf_set(lpfc_sli4_sge_last, sgl, 1);
	sgl->word2 = cpu_to_le32(sgl->word2);
	sgl->sge_len = cpu_to_le32(sizeof(struct fcp_rsp));

	/*
	 * Since the IOCB for the FCP I/O is built into this
	 * lpfc_io_buf, initialize it with all known data now.
	 */
	iocb = &lpfc_cmd->cur_iocbq.iocb;
	iocb->un.fcpi64.bdl.ulpIoTag32 = 0;
	iocb->un.fcpi64.bdl.bdeFlags = BUFF_TYPE_BDE_64;
	/* setting the BLP size to 2 * sizeof BDE may not be correct.
	 * We are setting the bpl to point to out sgl. An sgl's
	 * entries are 16 bytes, a bpl entries are 12 bytes.
	 */
	iocb->un.fcpi64.bdl.bdeSize = sizeof(struct fcp_cmnd);
	iocb->un.fcpi64.bdl.addrLow = putPaddrLow(pdma_phys_fcp_cmd);
	iocb->un.fcpi64.bdl.addrHigh = putPaddrHigh(pdma_phys_fcp_cmd);
	iocb->ulpBdeCount = 1;
	iocb->ulpLe = 1;
	iocb->ulpClass = CLASS3;

	if (lpfc_ndlp_check_qdepth(phba, ndlp)) {
		atomic_inc(&ndlp->cmd_pending);
		lpfc_cmd->flags |= LPFC_SBUF_BUMP_QDEPTH;
	}
	return  lpfc_cmd;
}