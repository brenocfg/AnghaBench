#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {TYPE_2__* phba; } ;
struct lpfc_nodelist {int nlp_rpi; int /*<<< orphan*/  nlp_DID; TYPE_1__* phba; struct lpfc_nodelist* active_rrqs_xri_bitmap; int /*<<< orphan*/  nlp_usg_map; int /*<<< orphan*/  kref; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_listp; } ;
struct TYPE_5__ {scalar_t__ sli_rev; int /*<<< orphan*/  active_rrq_pool; int /*<<< orphan*/  nlp_mem_pool; } ;
struct TYPE_4__ {int cfg_rrq_xri_bitmap_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NODE ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_NODE ; 
 int LPFC_RPI_ALLOC_ERROR ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_initialize_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpfc_nodelist*) ; 
 int lpfc_sli4_alloc_rpi (TYPE_2__*) ; 
 int /*<<< orphan*/  lpfc_sli4_free_rpi (TYPE_2__*,int) ; 
 void* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct lpfc_nodelist*,int /*<<< orphan*/ ,int) ; 

struct lpfc_nodelist *
lpfc_nlp_init(struct lpfc_vport *vport, uint32_t did)
{
	struct lpfc_nodelist *ndlp;
	int rpi = LPFC_RPI_ALLOC_ERROR;

	if (vport->phba->sli_rev == LPFC_SLI_REV4) {
		rpi = lpfc_sli4_alloc_rpi(vport->phba);
		if (rpi == LPFC_RPI_ALLOC_ERROR)
			return NULL;
	}

	ndlp = mempool_alloc(vport->phba->nlp_mem_pool, GFP_KERNEL);
	if (!ndlp) {
		if (vport->phba->sli_rev == LPFC_SLI_REV4)
			lpfc_sli4_free_rpi(vport->phba, rpi);
		return NULL;
	}

	memset(ndlp, 0, sizeof (struct lpfc_nodelist));

	lpfc_initialize_node(vport, ndlp, did);
	INIT_LIST_HEAD(&ndlp->nlp_listp);
	if (vport->phba->sli_rev == LPFC_SLI_REV4) {
		ndlp->nlp_rpi = rpi;
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NODE,
				 "0007 rpi:%x DID:%x flg:%x refcnt:%d "
				 "map:%x x%px\n", ndlp->nlp_rpi, ndlp->nlp_DID,
				 ndlp->nlp_flag,
				 kref_read(&ndlp->kref),
				 ndlp->nlp_usg_map, ndlp);

		ndlp->active_rrqs_xri_bitmap =
				mempool_alloc(vport->phba->active_rrq_pool,
					      GFP_KERNEL);
		if (ndlp->active_rrqs_xri_bitmap)
			memset(ndlp->active_rrqs_xri_bitmap, 0,
			       ndlp->phba->cfg_rrq_xri_bitmap_sz);
	}



	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_NODE,
		"node init:       did:x%x",
		ndlp->nlp_DID, 0, 0);

	return ndlp;
}