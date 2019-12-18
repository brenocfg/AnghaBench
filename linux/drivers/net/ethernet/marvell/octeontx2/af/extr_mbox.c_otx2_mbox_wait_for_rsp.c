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
struct otx2_mbox_dev {scalar_t__ num_msgs; scalar_t__ msgs_acked; } ;
struct otx2_mbox {struct otx2_mbox_dev* dev; } ;

/* Variables and functions */
 int EIO ; 
 int MBOX_RSP_TIMEOUT ; 
 int /*<<< orphan*/  msleep (int) ; 

int otx2_mbox_wait_for_rsp(struct otx2_mbox *mbox, int devid)
{
	struct otx2_mbox_dev *mdev = &mbox->dev[devid];
	int timeout = 0, sleep = 1;

	while (mdev->num_msgs != mdev->msgs_acked) {
		msleep(sleep);
		timeout += sleep;
		if (timeout >= MBOX_RSP_TIMEOUT)
			return -EIO;
	}
	return 0;
}