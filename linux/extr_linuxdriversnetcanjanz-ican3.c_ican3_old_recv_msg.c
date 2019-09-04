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
typedef  int u8 ;
struct ican3_msg {int dummy; } ;
struct ican3_dev {scalar_t__ dpm; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MSYNC_LOCL ; 
 scalar_t__ MSYNC_PEER ; 
 int MSYNC_RB0 ; 
 int MSYNC_RB1 ; 
 int MSYNC_RBLW ; 
 int MSYNC_RB_MASK ; 
 unsigned int QUEUE_OLD_CONTROL ; 
 unsigned int QUEUE_OLD_RB0 ; 
 unsigned int QUEUE_OLD_RB1 ; 
 int /*<<< orphan*/  ican3_set_page (struct ican3_dev*,unsigned int) ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy_fromio (struct ican3_msg*,scalar_t__,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ican3_old_recv_msg(struct ican3_dev *mod, struct ican3_msg *msg)
{
	unsigned int mbox, mbox_page;
	u8 locl, peer, xord;

	/* get the MSYNC registers */
	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	peer = ioread8(mod->dpm + MSYNC_PEER);
	locl = ioread8(mod->dpm + MSYNC_LOCL);
	xord = locl ^ peer;

	if ((xord & MSYNC_RB_MASK) == 0x00) {
		netdev_dbg(mod->ndev, "no mbox for reading\n");
		return -ENOMEM;
	}

	/* find the first free mbox to read */
	if ((xord & MSYNC_RB_MASK) == MSYNC_RB_MASK)
		mbox = (xord & MSYNC_RBLW) ? MSYNC_RB0 : MSYNC_RB1;
	else
		mbox = (xord & MSYNC_RB0) ? MSYNC_RB0 : MSYNC_RB1;

	/* copy the message */
	mbox_page = (mbox == MSYNC_RB0) ? QUEUE_OLD_RB0 : QUEUE_OLD_RB1;
	ican3_set_page(mod, mbox_page);
	memcpy_fromio(msg, mod->dpm, sizeof(*msg));

	/*
	 * notify the firmware that the read buffer is available
	 * for it to fill again
	 */
	locl ^= mbox;

	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	iowrite8(locl, mod->dpm + MSYNC_LOCL);
	return 0;
}