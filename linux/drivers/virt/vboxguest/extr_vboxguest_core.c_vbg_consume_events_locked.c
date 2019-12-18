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
typedef  int u32 ;
struct vbg_session {int dummy; } ;
struct vbg_dev {int pending_events; } ;

/* Variables and functions */

__attribute__((used)) static u32 vbg_consume_events_locked(struct vbg_dev *gdev,
				     struct vbg_session *session,
				     u32 event_mask)
{
	u32 events = gdev->pending_events & event_mask;

	gdev->pending_events &= ~events;
	return events;
}