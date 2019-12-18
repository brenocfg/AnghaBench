#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union lpfc_sli4_cfg_shdr {int dummy; } lpfc_sli4_cfg_shdr ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_mbx_sge {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  request; } ;
struct lpfc_mbx_read_fcf_tbl {TYPE_2__ u; } ;
struct lpfc_hba {int dummy; } ;
struct lpfcMboxq {TYPE_1__* sge_array; } ;
struct fcf_record {int dummy; } ;
struct TYPE_3__ {void** addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 int /*<<< orphan*/  LPFC_MBOX_OPCODE_FCOE_READ_FCF_TABLE ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_FCOE ; 
 int /*<<< orphan*/  LPFC_SLI4_MBX_NEMBED ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbx_read_fcf_tbl_indx ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int lpfc_sli4_config (struct lpfc_hba*,struct lpfcMboxq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_mbx_sge_get (struct lpfcMboxq*,int /*<<< orphan*/ ,struct lpfc_mbx_sge*) ; 
 int /*<<< orphan*/  lpfc_sli_pcimem_bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
lpfc_sli4_mbx_read_fcf_rec(struct lpfc_hba *phba,
			   struct lpfcMboxq *mboxq,
			   uint16_t fcf_index)
{
	void *virt_addr;
	uint8_t *bytep;
	struct lpfc_mbx_sge sge;
	uint32_t alloc_len, req_len;
	struct lpfc_mbx_read_fcf_tbl *read_fcf;

	if (!mboxq)
		return -ENOMEM;

	req_len = sizeof(struct fcf_record) +
		  sizeof(union lpfc_sli4_cfg_shdr) + 2 * sizeof(uint32_t);

	/* Set up READ_FCF SLI4_CONFIG mailbox-ioctl command */
	alloc_len = lpfc_sli4_config(phba, mboxq, LPFC_MBOX_SUBSYSTEM_FCOE,
			LPFC_MBOX_OPCODE_FCOE_READ_FCF_TABLE, req_len,
			LPFC_SLI4_MBX_NEMBED);

	if (alloc_len < req_len) {
		lpfc_printf_log(phba, KERN_ERR, LOG_MBOX,
				"0291 Allocated DMA memory size (x%x) is "
				"less than the requested DMA memory "
				"size (x%x)\n", alloc_len, req_len);
		return -ENOMEM;
	}

	/* Get the first SGE entry from the non-embedded DMA memory. This
	 * routine only uses a single SGE.
	 */
	lpfc_sli4_mbx_sge_get(mboxq, 0, &sge);
	virt_addr = mboxq->sge_array->addr[0];
	read_fcf = (struct lpfc_mbx_read_fcf_tbl *)virt_addr;

	/* Set up command fields */
	bf_set(lpfc_mbx_read_fcf_tbl_indx, &read_fcf->u.request, fcf_index);
	/* Perform necessary endian conversion */
	bytep = virt_addr + sizeof(union lpfc_sli4_cfg_shdr);
	lpfc_sli_pcimem_bcopy(bytep, bytep, sizeof(uint32_t));

	return 0;
}