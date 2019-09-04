#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rc_dev {TYPE_1__* raw; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_6__ {int pulse; int /*<<< orphan*/  duration; } ;
struct TYPE_5__ {int /*<<< orphan*/  last_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IR_RAW_EVENT (TYPE_2__) ; 
 int EINVAL ; 
 TYPE_2__ ev ; 
 int ir_raw_event_store_with_timeout (struct rc_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 

int ir_raw_event_store_edge(struct rc_dev *dev, bool pulse)
{
	ktime_t			now;
	DEFINE_IR_RAW_EVENT(ev);

	if (!dev->raw)
		return -EINVAL;

	now = ktime_get();
	ev.duration = ktime_to_ns(ktime_sub(now, dev->raw->last_event));
	ev.pulse = !pulse;

	return ir_raw_event_store_with_timeout(dev, &ev);
}