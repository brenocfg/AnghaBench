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
struct rc_dev {TYPE_1__* raw; } ;
struct ir_raw_event {int pulse; int /*<<< orphan*/  duration; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  last_event; } ;

/* Variables and functions */
 int EINVAL ; 
 int ir_raw_event_store_with_timeout (struct rc_dev*,struct ir_raw_event*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 

int ir_raw_event_store_edge(struct rc_dev *dev, bool pulse)
{
	ktime_t			now;
	struct ir_raw_event	ev = {};

	if (!dev->raw)
		return -EINVAL;

	now = ktime_get();
	ev.duration = ktime_to_ns(ktime_sub(now, dev->raw->last_event));
	ev.pulse = !pulse;

	return ir_raw_event_store_with_timeout(dev, &ev);
}