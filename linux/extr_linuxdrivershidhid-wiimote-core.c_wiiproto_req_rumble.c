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
struct TYPE_2__ {int flags; } ;
struct wiimote_data {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int __u8 ;

/* Variables and functions */
 int WIIPROTO_FLAG_RUMBLE ; 
 int WIIPROTO_REQ_RUMBLE ; 
 int /*<<< orphan*/  wiimote_queue (struct wiimote_data*,int*,int) ; 
 int /*<<< orphan*/  wiiproto_keep_rumble (struct wiimote_data*,int*) ; 

void wiiproto_req_rumble(struct wiimote_data *wdata, __u8 rumble)
{
	__u8 cmd[2];

	rumble = !!rumble;
	if (rumble == !!(wdata->state.flags & WIIPROTO_FLAG_RUMBLE))
		return;

	if (rumble)
		wdata->state.flags |= WIIPROTO_FLAG_RUMBLE;
	else
		wdata->state.flags &= ~WIIPROTO_FLAG_RUMBLE;

	cmd[0] = WIIPROTO_REQ_RUMBLE;
	cmd[1] = 0;

	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}