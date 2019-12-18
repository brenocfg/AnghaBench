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
struct TYPE_3__ {scalar_t__ type; } ;
struct perf_event {int /*<<< orphan*/  destroy; TYPE_1__ attr; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int ENOENT ; 
 int etm_addr_filters_alloc (struct perf_event*) ; 
 int /*<<< orphan*/  etm_event_destroy ; 
 TYPE_2__ etm_pmu ; 

__attribute__((used)) static int etm_event_init(struct perf_event *event)
{
	int ret = 0;

	if (event->attr.type != etm_pmu.type) {
		ret = -ENOENT;
		goto out;
	}

	ret = etm_addr_filters_alloc(event);
	if (ret)
		goto out;

	event->destroy = etm_event_destroy;
out:
	return ret;
}