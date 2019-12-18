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
struct wl1251 {scalar_t__* mbox_ptr; } ;
struct event_mailbox {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int /*<<< orphan*/  REG_EVENT_MAILBOX_PTR ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ wl1251_reg_read32 (struct wl1251*,int /*<<< orphan*/ ) ; 

void wl1251_event_mbox_config(struct wl1251 *wl)
{
	wl->mbox_ptr[0] = wl1251_reg_read32(wl, REG_EVENT_MAILBOX_PTR);
	wl->mbox_ptr[1] = wl->mbox_ptr[0] + sizeof(struct event_mailbox);

	wl1251_debug(DEBUG_EVENT, "MBOX ptrs: 0x%x 0x%x",
		     wl->mbox_ptr[0], wl->mbox_ptr[1]);
}