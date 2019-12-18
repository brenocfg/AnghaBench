#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_mbx_nembed_rsrc_extent {int /*<<< orphan*/  word4; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_8__ {struct lpfc_mbx_nembed_rsrc_extent req; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct TYPE_10__ {TYPE_3__ alloc_rsrc_extents; } ;
struct TYPE_11__ {TYPE_4__ un; } ;
struct TYPE_12__ {TYPE_5__ mqe; } ;
struct lpfcMboxq {TYPE_6__ u; TYPE_1__* sge_array; } ;
struct TYPE_7__ {void** addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_MBOX ; 
#define  LPFC_MBOX_OPCODE_ALLOC_RSRC_EXTENT 131 
#define  LPFC_MBOX_OPCODE_DEALLOC_RSRC_EXTENT 130 
#define  LPFC_MBOX_OPCODE_GET_ALLOC_RSRC_EXTENT 129 
#define  LPFC_MBOX_OPCODE_GET_RSRC_EXTENT_INFO 128 
 int LPFC_SLI4_MBX_EMBED ; 
 int LPFC_SLI4_MBX_NEMBED ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_mbx_nembed_rsrc_extent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbx_alloc_rsrc_extents_cnt ; 
 int /*<<< orphan*/  lpfc_mbx_alloc_rsrc_extents_type ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int lpfc_sli_config_mbox_opcode_get (struct lpfc_hba*,struct lpfcMboxq*) ; 
 int /*<<< orphan*/  lpfc_sli_pcimem_bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
lpfc_sli4_mbox_rsrc_extent(struct lpfc_hba *phba, struct lpfcMboxq *mbox,
			   uint16_t exts_count, uint16_t rsrc_type, bool emb)
{
	uint8_t opcode = 0;
	struct lpfc_mbx_nembed_rsrc_extent *n_rsrc_extnt = NULL;
	void *virtaddr = NULL;

	/* Set up SLI4 ioctl command header fields */
	if (emb == LPFC_SLI4_MBX_NEMBED) {
		/* Get the first SGE entry from the non-embedded DMA memory */
		virtaddr = mbox->sge_array->addr[0];
		if (virtaddr == NULL)
			return 1;
		n_rsrc_extnt = (struct lpfc_mbx_nembed_rsrc_extent *) virtaddr;
	}

	/*
	 * The resource type is common to all extent Opcodes and resides in the
	 * same position.
	 */
	if (emb == LPFC_SLI4_MBX_EMBED)
		bf_set(lpfc_mbx_alloc_rsrc_extents_type,
		       &mbox->u.mqe.un.alloc_rsrc_extents.u.req,
		       rsrc_type);
	else {
		/* This is DMA data.  Byteswap is required. */
		bf_set(lpfc_mbx_alloc_rsrc_extents_type,
		       n_rsrc_extnt, rsrc_type);
		lpfc_sli_pcimem_bcopy(&n_rsrc_extnt->word4,
				      &n_rsrc_extnt->word4,
				      sizeof(uint32_t));
	}

	/* Complete the initialization for the particular Opcode. */
	opcode = lpfc_sli_config_mbox_opcode_get(phba, mbox);
	switch (opcode) {
	case LPFC_MBOX_OPCODE_ALLOC_RSRC_EXTENT:
		if (emb == LPFC_SLI4_MBX_EMBED)
			bf_set(lpfc_mbx_alloc_rsrc_extents_cnt,
			       &mbox->u.mqe.un.alloc_rsrc_extents.u.req,
			       exts_count);
		else
			bf_set(lpfc_mbx_alloc_rsrc_extents_cnt,
			       n_rsrc_extnt, exts_count);
		break;
	case LPFC_MBOX_OPCODE_GET_ALLOC_RSRC_EXTENT:
	case LPFC_MBOX_OPCODE_GET_RSRC_EXTENT_INFO:
	case LPFC_MBOX_OPCODE_DEALLOC_RSRC_EXTENT:
		/* Initialization is complete.*/
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_MBOX,
				"2929 Resource Extent Opcode x%x is "
				"unsupported\n", opcode);
		return 1;
	}

	return 0;
}