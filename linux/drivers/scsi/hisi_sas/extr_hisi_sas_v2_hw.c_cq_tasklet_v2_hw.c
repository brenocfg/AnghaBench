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
typedef  int u64 ;
typedef  size_t u32 ;
struct hisi_sas_slot {size_t cmplt_queue_slot; int cmplt_queue; } ;
struct hisi_sas_itct {int /*<<< orphan*/ * qw4_15; } ;
struct hisi_sas_cq {size_t rd_point; int id; struct hisi_hba* hisi_hba; } ;
struct hisi_sas_complete_v2_hdr {scalar_t__ dw1; scalar_t__ act; } ;
struct hisi_hba {struct hisi_sas_slot* slot_info; struct hisi_sas_itct* itct; struct hisi_sas_complete_v2_hdr** complete_hdr; int /*<<< orphan*/  reject_stp_links_msk; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 size_t CMPLT_HDR_DEV_ID_MSK ; 
 size_t CMPLT_HDR_DEV_ID_OFF ; 
 size_t CMPLT_HDR_IPTT_MSK ; 
 scalar_t__ COMPL_Q_0_RD_PTR ; 
 scalar_t__ COMPL_Q_0_WR_PTR ; 
 size_t HISI_SAS_QUEUE_SLOTS ; 
 int ffs (size_t) ; 
 size_t hisi_sas_read32 (struct hisi_hba*,scalar_t__) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,scalar_t__,size_t) ; 
 size_t le32_to_cpu (scalar_t__) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_try_accept_stp_links_v2_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  slot_complete_v2_hw (struct hisi_hba*,struct hisi_sas_slot*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cq_tasklet_v2_hw(unsigned long val)
{
	struct hisi_sas_cq *cq = (struct hisi_sas_cq *)val;
	struct hisi_hba *hisi_hba = cq->hisi_hba;
	struct hisi_sas_slot *slot;
	struct hisi_sas_itct *itct;
	struct hisi_sas_complete_v2_hdr *complete_queue;
	u32 rd_point = cq->rd_point, wr_point, dev_id;
	int queue = cq->id;

	if (unlikely(hisi_hba->reject_stp_links_msk))
		phys_try_accept_stp_links_v2_hw(hisi_hba);

	complete_queue = hisi_hba->complete_hdr[queue];

	wr_point = hisi_sas_read32(hisi_hba, COMPL_Q_0_WR_PTR +
				   (0x14 * queue));

	while (rd_point != wr_point) {
		struct hisi_sas_complete_v2_hdr *complete_hdr;
		int iptt;

		complete_hdr = &complete_queue[rd_point];

		/* Check for NCQ completion */
		if (complete_hdr->act) {
			u32 act_tmp = le32_to_cpu(complete_hdr->act);
			int ncq_tag_count = ffs(act_tmp);
			u32 dw1 = le32_to_cpu(complete_hdr->dw1);

			dev_id = (dw1 & CMPLT_HDR_DEV_ID_MSK) >>
				 CMPLT_HDR_DEV_ID_OFF;
			itct = &hisi_hba->itct[dev_id];

			/* The NCQ tags are held in the itct header */
			while (ncq_tag_count) {
				__le64 *_ncq_tag = &itct->qw4_15[0], __ncq_tag;
				u64 ncq_tag;

				ncq_tag_count--;
				__ncq_tag = _ncq_tag[ncq_tag_count / 5];
				ncq_tag = le64_to_cpu(__ncq_tag);
				iptt = (ncq_tag >> (ncq_tag_count % 5) * 12) &
				       0xfff;

				slot = &hisi_hba->slot_info[iptt];
				slot->cmplt_queue_slot = rd_point;
				slot->cmplt_queue = queue;
				slot_complete_v2_hw(hisi_hba, slot);

				act_tmp &= ~(1 << ncq_tag_count);
				ncq_tag_count = ffs(act_tmp);
			}
		} else {
			u32 dw1 = le32_to_cpu(complete_hdr->dw1);

			iptt = dw1 & CMPLT_HDR_IPTT_MSK;
			slot = &hisi_hba->slot_info[iptt];
			slot->cmplt_queue_slot = rd_point;
			slot->cmplt_queue = queue;
			slot_complete_v2_hw(hisi_hba, slot);
		}

		if (++rd_point >= HISI_SAS_QUEUE_SLOTS)
			rd_point = 0;
	}

	/* update rd_point */
	cq->rd_point = rd_point;
	hisi_sas_write32(hisi_hba, COMPL_Q_0_RD_PTR + (0x14 * queue), rd_point);
}