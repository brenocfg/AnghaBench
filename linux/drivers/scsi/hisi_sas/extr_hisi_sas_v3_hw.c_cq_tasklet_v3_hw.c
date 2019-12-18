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
struct hisi_sas_cq {size_t rd_point; int id; struct hisi_hba* hisi_hba; } ;
struct hisi_sas_complete_v3_hdr {int /*<<< orphan*/  dw1; } ;
struct hisi_hba {struct hisi_sas_slot* slot_info; struct device* dev; struct hisi_sas_complete_v3_hdr** complete_hdr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t CMPLT_HDR_IPTT_MSK ; 
 scalar_t__ COMPL_Q_0_RD_PTR ; 
 scalar_t__ COMPL_Q_0_WR_PTR ; 
 int HISI_SAS_COMMAND_ENTRIES_V3_HW ; 
 size_t HISI_SAS_QUEUE_SLOTS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 size_t hisi_sas_read32 (struct hisi_hba*,scalar_t__) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,scalar_t__,size_t) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  slot_complete_v3_hw (struct hisi_hba*,struct hisi_sas_slot*) ; 

__attribute__((used)) static void cq_tasklet_v3_hw(unsigned long val)
{
	struct hisi_sas_cq *cq = (struct hisi_sas_cq *)val;
	struct hisi_hba *hisi_hba = cq->hisi_hba;
	struct hisi_sas_slot *slot;
	struct hisi_sas_complete_v3_hdr *complete_queue;
	u32 rd_point = cq->rd_point, wr_point;
	int queue = cq->id;

	complete_queue = hisi_hba->complete_hdr[queue];

	wr_point = hisi_sas_read32(hisi_hba, COMPL_Q_0_WR_PTR +
				   (0x14 * queue));

	while (rd_point != wr_point) {
		struct hisi_sas_complete_v3_hdr *complete_hdr;
		struct device *dev = hisi_hba->dev;
		u32 dw1;
		int iptt;

		complete_hdr = &complete_queue[rd_point];
		dw1 = le32_to_cpu(complete_hdr->dw1);

		iptt = dw1 & CMPLT_HDR_IPTT_MSK;
		if (likely(iptt < HISI_SAS_COMMAND_ENTRIES_V3_HW)) {
			slot = &hisi_hba->slot_info[iptt];
			slot->cmplt_queue_slot = rd_point;
			slot->cmplt_queue = queue;
			slot_complete_v3_hw(hisi_hba, slot);
		} else
			dev_err(dev, "IPTT %d is invalid, discard it.\n", iptt);

		if (++rd_point >= HISI_SAS_QUEUE_SLOTS)
			rd_point = 0;
	}

	/* update rd_point */
	cq->rd_point = rd_point;
	hisi_sas_write32(hisi_hba, COMPL_Q_0_RD_PTR + (0x14 * queue), rd_point);
}