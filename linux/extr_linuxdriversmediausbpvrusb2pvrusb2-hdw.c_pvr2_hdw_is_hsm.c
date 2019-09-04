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
struct pvr2_hdw {scalar_t__* cmd_buffer; int /*<<< orphan*/  ctl_lock; } ;

/* Variables and functions */
 scalar_t__ FX2CMD_GET_USB_SPEED ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int pvr2_send_request (struct pvr2_hdw*,scalar_t__*,int,scalar_t__*,int) ; 

int pvr2_hdw_is_hsm(struct pvr2_hdw *hdw)
{
	int result;
	LOCK_TAKE(hdw->ctl_lock); do {
		hdw->cmd_buffer[0] = FX2CMD_GET_USB_SPEED;
		result = pvr2_send_request(hdw,
					   hdw->cmd_buffer,1,
					   hdw->cmd_buffer,1);
		if (result < 0) break;
		result = (hdw->cmd_buffer[0] != 0);
	} while(0); LOCK_GIVE(hdw->ctl_lock);
	return result;
}