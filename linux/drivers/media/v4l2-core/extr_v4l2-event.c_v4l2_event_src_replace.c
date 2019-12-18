#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  changes; } ;
struct TYPE_4__ {TYPE_1__ src_change; } ;
struct v4l2_event {TYPE_2__ u; } ;

/* Variables and functions */

__attribute__((used)) static void v4l2_event_src_replace(struct v4l2_event *old,
				const struct v4l2_event *new)
{
	u32 old_changes = old->u.src_change.changes;

	old->u.src_change = new->u.src_change;
	old->u.src_change.changes |= old_changes;
}