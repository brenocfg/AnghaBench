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
struct vbg_dev {int /*<<< orphan*/  heartbeat_interval_ms; int /*<<< orphan*/  heartbeat_timer; int /*<<< orphan*/  guest_heartbeat_req; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct vbg_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct vbg_dev* gdev ; 
 int /*<<< orphan*/  heartbeat_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_req_perform (struct vbg_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vbg_heartbeat_timer(struct timer_list *t)
{
	struct vbg_dev *gdev = from_timer(gdev, t, heartbeat_timer);

	vbg_req_perform(gdev, gdev->guest_heartbeat_req);
	mod_timer(&gdev->heartbeat_timer,
		  msecs_to_jiffies(gdev->heartbeat_interval_ms));
}