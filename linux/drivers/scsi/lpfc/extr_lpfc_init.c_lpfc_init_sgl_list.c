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
struct TYPE_2__ {scalar_t__ io_xri_cnt; scalar_t__ els_xri_cnt; int /*<<< orphan*/  lpfc_abts_nvmet_ctx_list; int /*<<< orphan*/  lpfc_nvmet_sgl_list; int /*<<< orphan*/  lpfc_abts_els_sgl_list; int /*<<< orphan*/  lpfc_els_sgl_list; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_init_sgl_list(struct lpfc_hba *phba)
{
	/* Initialize and populate the sglq list per host/VF. */
	INIT_LIST_HEAD(&phba->sli4_hba.lpfc_els_sgl_list);
	INIT_LIST_HEAD(&phba->sli4_hba.lpfc_abts_els_sgl_list);
	INIT_LIST_HEAD(&phba->sli4_hba.lpfc_nvmet_sgl_list);
	INIT_LIST_HEAD(&phba->sli4_hba.lpfc_abts_nvmet_ctx_list);

	/* els xri-sgl book keeping */
	phba->sli4_hba.els_xri_cnt = 0;

	/* nvme xri-buffer book keeping */
	phba->sli4_hba.io_xri_cnt = 0;
}