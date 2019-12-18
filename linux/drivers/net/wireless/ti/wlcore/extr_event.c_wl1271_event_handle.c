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
typedef  int u8 ;
struct wl1271 {TYPE_1__* ops; int /*<<< orphan*/  mbox_size; int /*<<< orphan*/  mbox; int /*<<< orphan*/ * mbox_ptr; } ;
struct TYPE_2__ {int (* process_mailbox_events ) (struct wl1271*) ;int (* ack_event ) (struct wl1271*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int EINVAL ; 
 int stub1 (struct wl1271*) ; 
 int stub2 (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 int wlcore_read (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int wl1271_event_handle(struct wl1271 *wl, u8 mbox_num)
{
	int ret;

	wl1271_debug(DEBUG_EVENT, "EVENT on mbox %d", mbox_num);

	if (mbox_num > 1)
		return -EINVAL;

	/* first we read the mbox descriptor */
	ret = wlcore_read(wl, wl->mbox_ptr[mbox_num], wl->mbox,
			  wl->mbox_size, false);
	if (ret < 0)
		return ret;

	/* process the descriptor */
	ret = wl->ops->process_mailbox_events(wl);
	if (ret < 0)
		return ret;

	/*
	 * TODO: we just need this because one bit is in a different
	 * place.  Is there any better way?
	 */
	ret = wl->ops->ack_event(wl);

	return ret;
}