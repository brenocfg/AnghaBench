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
struct sli4_sge_diseed {int word2; int word3; void* sge_len; void* addr_hi; void* addr_lo; void* ref_tag; void* ref_tag_tran; } ;
struct sli4_sge {int word2; int word3; void* sge_len; void* addr_hi; void* addr_lo; void* ref_tag; void* ref_tag_tran; } ;
struct sli4_hybrid_sgl {scalar_t__ dma_sgl; int /*<<< orphan*/  dma_phys_sgl; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct scatterlist {int dummy; } ;
struct lpfc_io_buf {scalar_t__ seg_cnt; } ;
struct lpfc_hba {int border_sge_num; int cfg_sg_dma_buf_size; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int BG_ERR_CHECK ; 
 int BG_ERR_SWAP ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  LPFC_CHECK_PROTECT_GUARD ; 
 int /*<<< orphan*/  LPFC_CHECK_PROTECT_REF ; 
 int LPFC_SGE_TYPE_DATA ; 
 int LPFC_SGE_TYPE_DISEED ; 
 int LPFC_SGE_TYPE_LSP ; 
 int bf_get (int /*<<< orphan*/ ,struct sli4_sge_diseed*) ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct sli4_sge_diseed*,int) ; 
 void* cpu_to_le32 (int) ; 
 int lpfc_bg_err_inject (struct lpfc_hba*,struct scsi_cmnd*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lpfc_bg_err_opcodes (struct lpfc_hba*,struct scsi_cmnd*,int*,int*) ; 
 scalar_t__ lpfc_cmd_protect (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 struct sli4_hybrid_sgl* lpfc_get_sgl_per_hdwq (struct lpfc_hba*,struct lpfc_io_buf*) ; 
 int lpfc_sc_to_bg_opcodes (struct lpfc_hba*,struct scsi_cmnd*,int*,int*) ; 
 int /*<<< orphan*/  lpfc_sli4_sge_dif_ai ; 
 int /*<<< orphan*/  lpfc_sli4_sge_dif_ce ; 
 int /*<<< orphan*/  lpfc_sli4_sge_dif_me ; 
 int /*<<< orphan*/  lpfc_sli4_sge_dif_oprx ; 
 int /*<<< orphan*/  lpfc_sli4_sge_dif_optx ; 
 int /*<<< orphan*/  lpfc_sli4_sge_dif_re ; 
 int /*<<< orphan*/  lpfc_sli4_sge_last ; 
 int /*<<< orphan*/  lpfc_sli4_sge_offset ; 
 int /*<<< orphan*/  lpfc_sli4_sge_type ; 
 int /*<<< orphan*/  memset (struct sli4_sge_diseed*,int /*<<< orphan*/ ,int) ; 
 int putPaddrHigh (int /*<<< orphan*/ ) ; 
 int putPaddrLow (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_get_lba (struct scsi_cmnd*) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
lpfc_bg_setup_sgl(struct lpfc_hba *phba, struct scsi_cmnd *sc,
		struct sli4_sge *sgl, int datasegcnt,
		struct lpfc_io_buf *lpfc_cmd)
{
	struct scatterlist *sgde = NULL; /* s/g data entry */
	struct sli4_sge_diseed *diseed = NULL;
	dma_addr_t physaddr;
	int i = 0, num_sge = 0, status;
	uint32_t reftag;
	uint8_t txop, rxop;
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	uint32_t rc;
#endif
	uint32_t checking = 1;
	uint32_t dma_len;
	uint32_t dma_offset = 0;
	struct sli4_hybrid_sgl *sgl_xtra = NULL;
	int j;
	bool lsp_just_set = false;

	status  = lpfc_sc_to_bg_opcodes(phba, sc, &txop, &rxop);
	if (status)
		goto out;

	/* extract some info from the scsi command for pde*/
	reftag = (uint32_t)scsi_get_lba(sc); /* Truncate LBA */

#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	rc = lpfc_bg_err_inject(phba, sc, &reftag, NULL, 1);
	if (rc) {
		if (rc & BG_ERR_SWAP)
			lpfc_bg_err_opcodes(phba, sc, &txop, &rxop);
		if (rc & BG_ERR_CHECK)
			checking = 0;
	}
#endif

	/* setup DISEED with what we have */
	diseed = (struct sli4_sge_diseed *) sgl;
	memset(diseed, 0, sizeof(struct sli4_sge_diseed));
	bf_set(lpfc_sli4_sge_type, sgl, LPFC_SGE_TYPE_DISEED);

	/* Endianness conversion if necessary */
	diseed->ref_tag = cpu_to_le32(reftag);
	diseed->ref_tag_tran = diseed->ref_tag;

	/*
	 * We only need to check the data on READs, for WRITEs
	 * protection data is automatically generated, not checked.
	 */
	if (sc->sc_data_direction == DMA_FROM_DEVICE) {
		if (lpfc_cmd_protect(sc, LPFC_CHECK_PROTECT_GUARD))
			bf_set(lpfc_sli4_sge_dif_ce, diseed, checking);
		else
			bf_set(lpfc_sli4_sge_dif_ce, diseed, 0);

		if (lpfc_cmd_protect(sc, LPFC_CHECK_PROTECT_REF))
			bf_set(lpfc_sli4_sge_dif_re, diseed, checking);
		else
			bf_set(lpfc_sli4_sge_dif_re, diseed, 0);
	}

	/* setup DISEED with the rest of the info */
	bf_set(lpfc_sli4_sge_dif_optx, diseed, txop);
	bf_set(lpfc_sli4_sge_dif_oprx, diseed, rxop);

	bf_set(lpfc_sli4_sge_dif_ai, diseed, 1);
	bf_set(lpfc_sli4_sge_dif_me, diseed, 0);

	/* Endianness conversion if necessary for DISEED */
	diseed->word2 = cpu_to_le32(diseed->word2);
	diseed->word3 = cpu_to_le32(diseed->word3);

	/* advance bpl and increment sge count */
	num_sge++;
	sgl++;

	/* assumption: caller has already run dma_map_sg on command data */
	sgde = scsi_sglist(sc);
	j = 3;
	for (i = 0; i < datasegcnt; i++) {
		/* clear it */
		sgl->word2 = 0;

		/* do we need to expand the segment */
		if (!lsp_just_set && !((j + 1) % phba->border_sge_num) &&
		    ((datasegcnt - 1) != i)) {
			/* set LSP type */
			bf_set(lpfc_sli4_sge_type, sgl, LPFC_SGE_TYPE_LSP);

			sgl_xtra = lpfc_get_sgl_per_hdwq(phba, lpfc_cmd);

			if (unlikely(!sgl_xtra)) {
				lpfc_cmd->seg_cnt = 0;
				return 0;
			}
			sgl->addr_lo = cpu_to_le32(putPaddrLow(
						sgl_xtra->dma_phys_sgl));
			sgl->addr_hi = cpu_to_le32(putPaddrHigh(
						sgl_xtra->dma_phys_sgl));

		} else {
			bf_set(lpfc_sli4_sge_type, sgl, LPFC_SGE_TYPE_DATA);
		}

		if (!(bf_get(lpfc_sli4_sge_type, sgl) & LPFC_SGE_TYPE_LSP)) {
			if ((datasegcnt - 1) == i)
				bf_set(lpfc_sli4_sge_last, sgl, 1);
			physaddr = sg_dma_address(sgde);
			dma_len = sg_dma_len(sgde);
			sgl->addr_lo = cpu_to_le32(putPaddrLow(physaddr));
			sgl->addr_hi = cpu_to_le32(putPaddrHigh(physaddr));

			bf_set(lpfc_sli4_sge_offset, sgl, dma_offset);
			sgl->word2 = cpu_to_le32(sgl->word2);
			sgl->sge_len = cpu_to_le32(dma_len);

			dma_offset += dma_len;
			sgde = sg_next(sgde);

			sgl++;
			num_sge++;
			lsp_just_set = false;

		} else {
			sgl->word2 = cpu_to_le32(sgl->word2);
			sgl->sge_len = cpu_to_le32(phba->cfg_sg_dma_buf_size);

			sgl = (struct sli4_sge *)sgl_xtra->dma_sgl;
			i = i - 1;

			lsp_just_set = true;
		}

		j++;

	}

out:
	return num_sge;
}