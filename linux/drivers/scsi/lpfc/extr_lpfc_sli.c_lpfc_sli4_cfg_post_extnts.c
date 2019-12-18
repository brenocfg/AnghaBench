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
typedef  union lpfc_sli4_cfg_shdr {int dummy; } lpfc_sli4_cfg_shdr ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct mbox_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  intr_enable; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;
typedef  int /*<<< orphan*/  MAILBOX_t ;
typedef  int /*<<< orphan*/  LPFC_MBOXQ_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_MBOX_OPCODE_ALLOC_RSRC_EXTENT ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_COMMON ; 
 int LPFC_SLI4_MBX_EMBED ; 
 int LPFC_SLI4_MBX_NEMBED ; 
 int /*<<< orphan*/  MBX_POLL ; 
 int lpfc_mbox_tmo_val (struct lpfc_hba*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int lpfc_sli4_config (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int lpfc_sli4_mbox_rsrc_extent (struct lpfc_hba*,int /*<<< orphan*/ *,int,int,int) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_mbox_wait (struct lpfc_hba*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
lpfc_sli4_cfg_post_extnts(struct lpfc_hba *phba, uint16_t extnt_cnt,
			  uint16_t type, bool *emb, LPFC_MBOXQ_t *mbox)
{
	int rc = 0;
	uint32_t req_len;
	uint32_t emb_len;
	uint32_t alloc_len, mbox_tmo;

	/* Calculate the total requested length of the dma memory */
	req_len = extnt_cnt * sizeof(uint16_t);

	/*
	 * Calculate the size of an embedded mailbox.  The uint32_t
	 * accounts for extents-specific word.
	 */
	emb_len = sizeof(MAILBOX_t) - sizeof(struct mbox_header) -
		sizeof(uint32_t);

	/*
	 * Presume the allocation and response will fit into an embedded
	 * mailbox.  If not true, reconfigure to a non-embedded mailbox.
	 */
	*emb = LPFC_SLI4_MBX_EMBED;
	if (req_len > emb_len) {
		req_len = extnt_cnt * sizeof(uint16_t) +
			sizeof(union lpfc_sli4_cfg_shdr) +
			sizeof(uint32_t);
		*emb = LPFC_SLI4_MBX_NEMBED;
	}

	alloc_len = lpfc_sli4_config(phba, mbox, LPFC_MBOX_SUBSYSTEM_COMMON,
				     LPFC_MBOX_OPCODE_ALLOC_RSRC_EXTENT,
				     req_len, *emb);
	if (alloc_len < req_len) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2982 Allocated DMA memory size (x%x) is "
			"less than the requested DMA memory "
			"size (x%x)\n", alloc_len, req_len);
		return -ENOMEM;
	}
	rc = lpfc_sli4_mbox_rsrc_extent(phba, mbox, extnt_cnt, type, *emb);
	if (unlikely(rc))
		return -EIO;

	if (!phba->sli4_hba.intr_enable)
		rc = lpfc_sli_issue_mbox(phba, mbox, MBX_POLL);
	else {
		mbox_tmo = lpfc_mbox_tmo_val(phba, mbox);
		rc = lpfc_sli_issue_mbox_wait(phba, mbox, mbox_tmo);
	}

	if (unlikely(rc))
		rc = -EIO;
	return rc;
}