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
struct hisi_sas_cq {int /*<<< orphan*/  tasklet; } ;
struct hisi_hba {int cq_nvecs; struct hisi_sas_cq* cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void hisi_sas_kill_tasklets(struct hisi_hba *hisi_hba)
{
	int i;

	for (i = 0; i < hisi_hba->cq_nvecs; i++) {
		struct hisi_sas_cq *cq = &hisi_hba->cq[i];

		tasklet_kill(&cq->tasklet);
	}
}