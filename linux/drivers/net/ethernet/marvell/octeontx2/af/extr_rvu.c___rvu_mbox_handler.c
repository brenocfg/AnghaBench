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
struct rvu_work {struct rvu* rvu; } ;
struct otx2_mbox {int rx_start; struct otx2_mbox_dev* dev; } ;
struct mbox_wq_info {struct otx2_mbox mbox; struct rvu_work* mbox_wrk; } ;
struct rvu {int /*<<< orphan*/  dev; struct mbox_wq_info afvf_wq_info; struct mbox_wq_info afpf_wq_info; } ;
struct otx2_mbox_dev {struct mbox_msghdr* mbase; } ;
struct mbox_msghdr {int num_msgs; int pcifunc; int next_msgoff; int /*<<< orphan*/  id; } ;
struct mbox_hdr {int num_msgs; int pcifunc; int next_msgoff; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_MSG_ALIGN ; 
 int RVU_PFVF_FUNC_MASK ; 
 int RVU_PFVF_FUNC_SHIFT ; 
 int RVU_PFVF_PF_MASK ; 
 int RVU_PFVF_PF_SHIFT ; 
#define  TYPE_AFPF 129 
#define  TYPE_AFVF 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  otx2_mbox_id2name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otx2_mbox_msg_send (struct otx2_mbox*,int) ; 
 int rvu_process_mbox_msg (struct otx2_mbox*,int,struct mbox_msghdr*) ; 

__attribute__((used)) static void __rvu_mbox_handler(struct rvu_work *mwork, int type)
{
	struct rvu *rvu = mwork->rvu;
	int offset, err, id, devid;
	struct otx2_mbox_dev *mdev;
	struct mbox_hdr *req_hdr;
	struct mbox_msghdr *msg;
	struct mbox_wq_info *mw;
	struct otx2_mbox *mbox;

	switch (type) {
	case TYPE_AFPF:
		mw = &rvu->afpf_wq_info;
		break;
	case TYPE_AFVF:
		mw = &rvu->afvf_wq_info;
		break;
	default:
		return;
	}

	devid = mwork - mw->mbox_wrk;
	mbox = &mw->mbox;
	mdev = &mbox->dev[devid];

	/* Process received mbox messages */
	req_hdr = mdev->mbase + mbox->rx_start;
	if (req_hdr->num_msgs == 0)
		return;

	offset = mbox->rx_start + ALIGN(sizeof(*req_hdr), MBOX_MSG_ALIGN);

	for (id = 0; id < req_hdr->num_msgs; id++) {
		msg = mdev->mbase + offset;

		/* Set which PF/VF sent this message based on mbox IRQ */
		switch (type) {
		case TYPE_AFPF:
			msg->pcifunc &=
				~(RVU_PFVF_PF_MASK << RVU_PFVF_PF_SHIFT);
			msg->pcifunc |= (devid << RVU_PFVF_PF_SHIFT);
			break;
		case TYPE_AFVF:
			msg->pcifunc &=
				~(RVU_PFVF_FUNC_MASK << RVU_PFVF_FUNC_SHIFT);
			msg->pcifunc |= (devid << RVU_PFVF_FUNC_SHIFT) + 1;
			break;
		}

		err = rvu_process_mbox_msg(mbox, devid, msg);
		if (!err) {
			offset = mbox->rx_start + msg->next_msgoff;
			continue;
		}

		if (msg->pcifunc & RVU_PFVF_FUNC_MASK)
			dev_warn(rvu->dev, "Error %d when processing message %s (0x%x) from PF%d:VF%d\n",
				 err, otx2_mbox_id2name(msg->id),
				 msg->id, devid,
				 (msg->pcifunc & RVU_PFVF_FUNC_MASK) - 1);
		else
			dev_warn(rvu->dev, "Error %d when processing message %s (0x%x) from PF%d\n",
				 err, otx2_mbox_id2name(msg->id),
				 msg->id, devid);
	}

	/* Send mbox responses to VF/PF */
	otx2_mbox_msg_send(mbox, devid);
}