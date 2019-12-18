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
typedef  scalar_t__ u16 ;
struct otx2_mbox_dev {scalar_t__ num_msgs; scalar_t__ msgs_acked; struct mbox_msghdr* mbase; } ;
struct otx2_mbox {unsigned long tx_start; unsigned long rx_start; struct otx2_mbox_dev* dev; } ;
struct mbox_msghdr {scalar_t__ id; unsigned long next_msgoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct mbox_msghdr* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned long msgs_offset ; 

struct mbox_msghdr *otx2_mbox_get_rsp(struct otx2_mbox *mbox, int devid,
				      struct mbox_msghdr *msg)
{
	unsigned long imsg = mbox->tx_start + msgs_offset;
	unsigned long irsp = mbox->rx_start + msgs_offset;
	struct otx2_mbox_dev *mdev = &mbox->dev[devid];
	u16 msgs;

	if (mdev->num_msgs != mdev->msgs_acked)
		return ERR_PTR(-ENODEV);

	for (msgs = 0; msgs < mdev->msgs_acked; msgs++) {
		struct mbox_msghdr *pmsg = mdev->mbase + imsg;
		struct mbox_msghdr *prsp = mdev->mbase + irsp;

		if (msg == pmsg) {
			if (pmsg->id != prsp->id)
				return ERR_PTR(-ENODEV);
			return prsp;
		}

		imsg = pmsg->next_msgoff;
		irsp = prsp->next_msgoff;
	}

	return ERR_PTR(-ENODEV);
}