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
struct ap_queue {int dummy; } ;
typedef  enum ap_wait { ____Placeholder_ap_wait } ap_wait ;
typedef  enum ap_event { ____Placeholder_ap_event } ap_event ;

/* Variables and functions */
 int AP_WAIT_AGAIN ; 
 int ap_sm_event (struct ap_queue*,int) ; 

enum ap_wait ap_sm_event_loop(struct ap_queue *aq, enum ap_event event)
{
	enum ap_wait wait;

	while ((wait = ap_sm_event(aq, event)) == AP_WAIT_AGAIN)
		;
	return wait;
}