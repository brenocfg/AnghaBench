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
struct pvr2_hdw {int state_decoder_ready; int state_stale; int /*<<< orphan*/  workpoll; } ;

/* Variables and functions */
 int /*<<< orphan*/  decoder_stabilization_timer ; 
 struct pvr2_hdw* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct pvr2_hdw* hdw ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_stbit (char*,int) ; 

__attribute__((used)) static void pvr2_hdw_decoder_stabilization_timeout(struct timer_list *t)
{
	struct pvr2_hdw *hdw = from_timer(hdw, t, decoder_stabilization_timer);
	hdw->state_decoder_ready = !0;
	trace_stbit("state_decoder_ready", hdw->state_decoder_ready);
	hdw->state_stale = !0;
	schedule_work(&hdw->workpoll);
}