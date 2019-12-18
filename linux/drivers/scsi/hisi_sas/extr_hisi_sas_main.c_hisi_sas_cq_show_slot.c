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
struct seq_file {int dummy; } ;
struct hisi_sas_cq {size_t id; struct hisi_hba* hisi_hba; } ;
struct hisi_hba {TYPE_1__* hw; void** debugfs_complete_hdr; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int complete_hdr_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_sas_show_row_32 (struct seq_file*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_sas_cq_show_slot(struct seq_file *s, int slot, void *cq_ptr)
{
	struct hisi_sas_cq *cq = cq_ptr;
	struct hisi_hba *hisi_hba = cq->hisi_hba;
	void *complete_queue = hisi_hba->debugfs_complete_hdr[cq->id];
	__le32 *complete_hdr = complete_queue +
			(hisi_hba->hw->complete_hdr_size * slot);

	hisi_sas_show_row_32(s, slot,
			     hisi_hba->hw->complete_hdr_size,
			     complete_hdr);
}