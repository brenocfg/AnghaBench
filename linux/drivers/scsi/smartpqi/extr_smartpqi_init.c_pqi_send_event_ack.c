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
struct pqi_queue_group {int* iq_pi_copy; int /*<<< orphan*/ * submit_lock; int /*<<< orphan*/ * iq_pi; void** iq_element_array; int /*<<< orphan*/ * iq_ci; int /*<<< orphan*/  oq_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  response_queue_id; } ;
struct pqi_event_acknowledge_request {TYPE_1__ header; } ;
struct pqi_ctrl_info {int num_elements_per_iq; struct pqi_queue_group* queue_groups; } ;
typedef  int pqi_index_t ;

/* Variables and functions */
 size_t PQI_DEFAULT_QUEUE_GROUP ; 
 int PQI_OPERATIONAL_IQ_ELEMENT_LENGTH ; 
 size_t RAID_PATH ; 
 int /*<<< orphan*/  memcpy (void*,struct pqi_event_acknowledge_request*,size_t) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_num_elements_free (int,int,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_send_event_ack(struct pqi_ctrl_info *ctrl_info,
	struct pqi_event_acknowledge_request *iu, size_t iu_length)
{
	pqi_index_t iq_pi;
	pqi_index_t iq_ci;
	unsigned long flags;
	void *next_element;
	struct pqi_queue_group *queue_group;

	queue_group = &ctrl_info->queue_groups[PQI_DEFAULT_QUEUE_GROUP];
	put_unaligned_le16(queue_group->oq_id, &iu->header.response_queue_id);

	while (1) {
		spin_lock_irqsave(&queue_group->submit_lock[RAID_PATH], flags);

		iq_pi = queue_group->iq_pi_copy[RAID_PATH];
		iq_ci = readl(queue_group->iq_ci[RAID_PATH]);

		if (pqi_num_elements_free(iq_pi, iq_ci,
			ctrl_info->num_elements_per_iq))
			break;

		spin_unlock_irqrestore(
			&queue_group->submit_lock[RAID_PATH], flags);

		if (pqi_ctrl_offline(ctrl_info))
			return;
	}

	next_element = queue_group->iq_element_array[RAID_PATH] +
		(iq_pi * PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);

	memcpy(next_element, iu, iu_length);

	iq_pi = (iq_pi + 1) % ctrl_info->num_elements_per_iq;
	queue_group->iq_pi_copy[RAID_PATH] = iq_pi;

	/*
	 * This write notifies the controller that an IU is available to be
	 * processed.
	 */
	writel(iq_pi, queue_group->iq_pi[RAID_PATH]);

	spin_unlock_irqrestore(&queue_group->submit_lock[RAID_PATH], flags);
}