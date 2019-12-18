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
struct timer_list {int dummy; } ;
struct pvr2_hdw {int ctl_timeout_flag; int /*<<< orphan*/  ctl_read_urb; scalar_t__ ctl_read_pend_flag; int /*<<< orphan*/  ctl_write_urb; scalar_t__ ctl_write_pend_flag; } ;
struct hdw_timer {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 struct hdw_timer* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct hdw_timer* timer ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvr2_ctl_timeout(struct timer_list *t)
{
	struct hdw_timer *timer = from_timer(timer, t, timer);
	struct pvr2_hdw *hdw = timer->hdw;

	if (hdw->ctl_write_pend_flag || hdw->ctl_read_pend_flag) {
		hdw->ctl_timeout_flag = !0;
		if (hdw->ctl_write_pend_flag)
			usb_unlink_urb(hdw->ctl_write_urb);
		if (hdw->ctl_read_pend_flag)
			usb_unlink_urb(hdw->ctl_read_urb);
	}
}