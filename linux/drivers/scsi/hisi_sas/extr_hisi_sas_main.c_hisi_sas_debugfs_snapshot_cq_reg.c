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
struct hisi_hba {int queue_count; int /*<<< orphan*/ * complete_hdr; int /*<<< orphan*/ * debugfs_complete_hdr; TYPE_1__* hw; } ;
struct TYPE_2__ {int complete_hdr_size; } ;

/* Variables and functions */
 int HISI_SAS_QUEUE_SLOTS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hisi_sas_debugfs_snapshot_cq_reg(struct hisi_hba *hisi_hba)
{
	int queue_entry_size = hisi_hba->hw->complete_hdr_size;
	int i;

	for (i = 0; i < hisi_hba->queue_count; i++)
		memcpy(hisi_hba->debugfs_complete_hdr[i],
		       hisi_hba->complete_hdr[i],
		       HISI_SAS_QUEUE_SLOTS * queue_entry_size);
}