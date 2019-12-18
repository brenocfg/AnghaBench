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
struct scsi_cmnd {TYPE_1__* request; } ;
struct hisi_hba {int slot_index_count; int last_slot_index; int /*<<< orphan*/  lock; void* slot_index_tags; } ;
struct TYPE_2__ {int tag; } ;

/* Variables and functions */
 int HISI_SAS_UNRESERVED_IPTT ; 
 int SAS_QUEUE_FULL ; 
 int find_next_zero_bit (void*,int,int) ; 
 int /*<<< orphan*/  hisi_sas_slot_index_set (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hisi_sas_slot_index_alloc(struct hisi_hba *hisi_hba,
				     struct scsi_cmnd *scsi_cmnd)
{
	int index;
	void *bitmap = hisi_hba->slot_index_tags;
	unsigned long flags;

	if (scsi_cmnd)
		return scsi_cmnd->request->tag;

	spin_lock_irqsave(&hisi_hba->lock, flags);
	index = find_next_zero_bit(bitmap, hisi_hba->slot_index_count,
				   hisi_hba->last_slot_index + 1);
	if (index >= hisi_hba->slot_index_count) {
		index = find_next_zero_bit(bitmap,
				hisi_hba->slot_index_count,
				HISI_SAS_UNRESERVED_IPTT);
		if (index >= hisi_hba->slot_index_count) {
			spin_unlock_irqrestore(&hisi_hba->lock, flags);
			return -SAS_QUEUE_FULL;
		}
	}
	hisi_sas_slot_index_set(hisi_hba, index);
	hisi_hba->last_slot_index = index;
	spin_unlock_irqrestore(&hisi_hba->lock, flags);

	return index;
}