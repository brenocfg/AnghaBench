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
struct mbox_wq_info {struct otx2_mbox mbox_up; struct rvu_work* mbox_wrk_up; } ;
struct rvu {int /*<<< orphan*/  dev; struct mbox_wq_info afvf_wq_info; struct mbox_wq_info afpf_wq_info; } ;
struct otx2_mbox_dev {int /*<<< orphan*/  msgs_acked; struct mbox_msghdr* mbase; } ;
struct mbox_msghdr {int num_msgs; int id; scalar_t__ sig; scalar_t__ rc; int next_msgoff; } ;
struct mbox_hdr {int num_msgs; int id; scalar_t__ sig; scalar_t__ rc; int next_msgoff; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_MSG_ALIGN ; 
#define  MBOX_MSG_CGX_LINK_EVENT 130 
 int MBOX_MSG_MAX ; 
 scalar_t__ OTX2_MBOX_RSP_SIG ; 
#define  TYPE_AFPF 129 
#define  TYPE_AFVF 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  otx2_mbox_reset (struct otx2_mbox*,int) ; 

__attribute__((used)) static void __rvu_mbox_up_handler(struct rvu_work *mwork, int type)
{
	struct rvu *rvu = mwork->rvu;
	struct otx2_mbox_dev *mdev;
	struct mbox_hdr *rsp_hdr;
	struct mbox_msghdr *msg;
	struct mbox_wq_info *mw;
	struct otx2_mbox *mbox;
	int offset, id, devid;

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

	devid = mwork - mw->mbox_wrk_up;
	mbox = &mw->mbox_up;
	mdev = &mbox->dev[devid];

	rsp_hdr = mdev->mbase + mbox->rx_start;
	if (rsp_hdr->num_msgs == 0) {
		dev_warn(rvu->dev, "mbox up handler: num_msgs = 0\n");
		return;
	}

	offset = mbox->rx_start + ALIGN(sizeof(*rsp_hdr), MBOX_MSG_ALIGN);

	for (id = 0; id < rsp_hdr->num_msgs; id++) {
		msg = mdev->mbase + offset;

		if (msg->id >= MBOX_MSG_MAX) {
			dev_err(rvu->dev,
				"Mbox msg with unknown ID 0x%x\n", msg->id);
			goto end;
		}

		if (msg->sig != OTX2_MBOX_RSP_SIG) {
			dev_err(rvu->dev,
				"Mbox msg with wrong signature %x, ID 0x%x\n",
				msg->sig, msg->id);
			goto end;
		}

		switch (msg->id) {
		case MBOX_MSG_CGX_LINK_EVENT:
			break;
		default:
			if (msg->rc)
				dev_err(rvu->dev,
					"Mbox msg response has err %d, ID 0x%x\n",
					msg->rc, msg->id);
			break;
		}
end:
		offset = mbox->rx_start + msg->next_msgoff;
		mdev->msgs_acked++;
	}

	otx2_mbox_reset(mbox, devid);
}