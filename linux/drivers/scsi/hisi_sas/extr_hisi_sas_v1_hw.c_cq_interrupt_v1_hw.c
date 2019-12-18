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
typedef  size_t u32 ;
struct hisi_sas_slot {size_t cmplt_queue_slot; int cmplt_queue; } ;
struct hisi_sas_cq {int id; size_t rd_point; struct hisi_hba* hisi_hba; } ;
struct hisi_sas_complete_v1_hdr {int /*<<< orphan*/  data; } ;
struct hisi_hba {int /*<<< orphan*/  lock; struct hisi_sas_slot* slot_info; scalar_t__* complete_hdr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t CMPLT_HDR_IPTT_MSK ; 
 size_t CMPLT_HDR_IPTT_OFF ; 
 scalar_t__ COMPL_Q_0_RD_PTR ; 
 scalar_t__ COMPL_Q_0_WR_PTR ; 
 size_t HISI_SAS_QUEUE_SLOTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ OQ_INT_SRC ; 
 size_t hisi_sas_read32 (struct hisi_hba*,scalar_t__) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,scalar_t__,size_t) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_complete_v1_hw (struct hisi_hba*,struct hisi_sas_slot*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cq_interrupt_v1_hw(int irq, void *p)
{
	struct hisi_sas_cq *cq = p;
	struct hisi_hba *hisi_hba = cq->hisi_hba;
	struct hisi_sas_slot *slot;
	int queue = cq->id;
	struct hisi_sas_complete_v1_hdr *complete_queue =
			(struct hisi_sas_complete_v1_hdr *)
			hisi_hba->complete_hdr[queue];
	u32 rd_point = cq->rd_point, wr_point;

	spin_lock(&hisi_hba->lock);
	hisi_sas_write32(hisi_hba, OQ_INT_SRC, 1 << queue);
	wr_point = hisi_sas_read32(hisi_hba,
			COMPL_Q_0_WR_PTR + (0x14 * queue));

	while (rd_point != wr_point) {
		struct hisi_sas_complete_v1_hdr *complete_hdr;
		int idx;
		u32 cmplt_hdr_data;

		complete_hdr = &complete_queue[rd_point];
		cmplt_hdr_data = le32_to_cpu(complete_hdr->data);
		idx = (cmplt_hdr_data & CMPLT_HDR_IPTT_MSK) >>
		      CMPLT_HDR_IPTT_OFF;
		slot = &hisi_hba->slot_info[idx];

		/* The completion queue and queue slot index are not
		 * necessarily the same as the delivery queue and
		 * queue slot index.
		 */
		slot->cmplt_queue_slot = rd_point;
		slot->cmplt_queue = queue;
		slot_complete_v1_hw(hisi_hba, slot);

		if (++rd_point >= HISI_SAS_QUEUE_SLOTS)
			rd_point = 0;
	}

	/* update rd_point */
	cq->rd_point = rd_point;
	hisi_sas_write32(hisi_hba, COMPL_Q_0_RD_PTR + (0x14 * queue), rd_point);
	spin_unlock(&hisi_hba->lock);

	return IRQ_HANDLED;
}