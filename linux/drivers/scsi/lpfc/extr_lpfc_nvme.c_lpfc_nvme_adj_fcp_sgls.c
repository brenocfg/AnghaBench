#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sli4_sge {int addr_lo; int word2; void* sge_len; void* addr_hi; } ;
struct TYPE_7__ {int bdeSize; int /*<<< orphan*/  bdeFlags; } ;
struct TYPE_8__ {TYPE_2__ f; } ;
struct TYPE_9__ {int addrLow; void* addrHigh; TYPE_3__ tus; } ;
struct TYPE_10__ {struct sli4_sge wqe_com; TYPE_4__ bde; } ;
union lpfc_wqe128 {TYPE_5__ generic; int /*<<< orphan*/ * words; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nvmefc_fcp_req {int cmdlen; int rsplen; scalar_t__ sg_cnt; int /*<<< orphan*/  rspdma; int /*<<< orphan*/  cmddma; scalar_t__ cmdaddr; } ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_6__ {union lpfc_wqe128 wqe; } ;
struct lpfc_io_buf {struct sli4_sge* dma_sgl; TYPE_1__ cur_iocbq; } ;
struct lpfc_hba {scalar_t__ cfg_nvme_embed_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFF_TYPE_BDE_64 ; 
 int /*<<< orphan*/  BUFF_TYPE_BDE_IMMED ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct sli4_sge*,int) ; 
 void* cpu_to_le32 (int) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  lpfc_sli4_sge_last ; 
 int putPaddrHigh (int /*<<< orphan*/ ) ; 
 int putPaddrLow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqe_dbde ; 
 int /*<<< orphan*/  wqe_wqes ; 

__attribute__((used)) static inline void
lpfc_nvme_adj_fcp_sgls(struct lpfc_vport *vport,
		       struct lpfc_io_buf *lpfc_ncmd,
		       struct nvmefc_fcp_req *nCmd)
{
	struct lpfc_hba  *phba = vport->phba;
	struct sli4_sge *sgl;
	union lpfc_wqe128 *wqe;
	uint32_t *wptr, *dptr;

	/*
	 * Get a local pointer to the built-in wqe and correct
	 * the cmd size to match NVME's 96 bytes and fix
	 * the dma address.
	 */

	wqe = &lpfc_ncmd->cur_iocbq.wqe;

	/*
	 * Adjust the FCP_CMD and FCP_RSP DMA data and sge_len to
	 * match NVME.  NVME sends 96 bytes. Also, use the
	 * nvme commands command and response dma addresses
	 * rather than the virtual memory to ease the restore
	 * operation.
	 */
	sgl = lpfc_ncmd->dma_sgl;
	sgl->sge_len = cpu_to_le32(nCmd->cmdlen);
	if (phba->cfg_nvme_embed_cmd) {
		sgl->addr_hi = 0;
		sgl->addr_lo = 0;

		/* Word 0-2 - NVME CMND IU (embedded payload) */
		wqe->generic.bde.tus.f.bdeFlags = BUFF_TYPE_BDE_IMMED;
		wqe->generic.bde.tus.f.bdeSize = 56;
		wqe->generic.bde.addrHigh = 0;
		wqe->generic.bde.addrLow =  64;  /* Word 16 */

		/* Word 10  - dbde is 0, wqes is 1 in template */

		/*
		 * Embed the payload in the last half of the WQE
		 * WQE words 16-30 get the NVME CMD IU payload
		 *
		 * WQE words 16-19 get payload Words 1-4
		 * WQE words 20-21 get payload Words 6-7
		 * WQE words 22-29 get payload Words 16-23
		 */
		wptr = &wqe->words[16];  /* WQE ptr */
		dptr = (uint32_t *)nCmd->cmdaddr;  /* payload ptr */
		dptr++;			/* Skip Word 0 in payload */

		*wptr++ = *dptr++;	/* Word 1 */
		*wptr++ = *dptr++;	/* Word 2 */
		*wptr++ = *dptr++;	/* Word 3 */
		*wptr++ = *dptr++;	/* Word 4 */
		dptr++;			/* Skip Word 5 in payload */
		*wptr++ = *dptr++;	/* Word 6 */
		*wptr++ = *dptr++;	/* Word 7 */
		dptr += 8;		/* Skip Words 8-15 in payload */
		*wptr++ = *dptr++;	/* Word 16 */
		*wptr++ = *dptr++;	/* Word 17 */
		*wptr++ = *dptr++;	/* Word 18 */
		*wptr++ = *dptr++;	/* Word 19 */
		*wptr++ = *dptr++;	/* Word 20 */
		*wptr++ = *dptr++;	/* Word 21 */
		*wptr++ = *dptr++;	/* Word 22 */
		*wptr   = *dptr;	/* Word 23 */
	} else {
		sgl->addr_hi = cpu_to_le32(putPaddrHigh(nCmd->cmddma));
		sgl->addr_lo = cpu_to_le32(putPaddrLow(nCmd->cmddma));

		/* Word 0-2 - NVME CMND IU Inline BDE */
		wqe->generic.bde.tus.f.bdeFlags =  BUFF_TYPE_BDE_64;
		wqe->generic.bde.tus.f.bdeSize = nCmd->cmdlen;
		wqe->generic.bde.addrHigh = sgl->addr_hi;
		wqe->generic.bde.addrLow =  sgl->addr_lo;

		/* Word 10 */
		bf_set(wqe_dbde, &wqe->generic.wqe_com, 1);
		bf_set(wqe_wqes, &wqe->generic.wqe_com, 0);
	}

	sgl++;

	/* Setup the physical region for the FCP RSP */
	sgl->addr_hi = cpu_to_le32(putPaddrHigh(nCmd->rspdma));
	sgl->addr_lo = cpu_to_le32(putPaddrLow(nCmd->rspdma));
	sgl->word2 = le32_to_cpu(sgl->word2);
	if (nCmd->sg_cnt)
		bf_set(lpfc_sli4_sge_last, sgl, 0);
	else
		bf_set(lpfc_sli4_sge_last, sgl, 1);
	sgl->word2 = cpu_to_le32(sgl->word2);
	sgl->sge_len = cpu_to_le32(nCmd->rsplen);
}