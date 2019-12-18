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
struct TYPE_2__ {int newev; int /*<<< orphan*/  event; } ;
struct vt_event_wait {scalar_t__ done; TYPE_1__ event; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  VT_EVENT_SWITCH ; 
 int /*<<< orphan*/  __vt_event_dequeue (struct vt_event_wait*) ; 
 int /*<<< orphan*/  __vt_event_queue (struct vt_event_wait*) ; 
 int /*<<< orphan*/  __vt_event_wait (struct vt_event_wait*) ; 
 int fg_console ; 

int vt_waitactive(int n)
{
	struct vt_event_wait vw;
	do {
		vw.event.event = VT_EVENT_SWITCH;
		__vt_event_queue(&vw);
		if (n == fg_console + 1) {
			__vt_event_dequeue(&vw);
			break;
		}
		__vt_event_wait(&vw);
		__vt_event_dequeue(&vw);
		if (vw.done == 0)
			return -EINTR;
	} while (vw.event.newev != n);
	return 0;
}