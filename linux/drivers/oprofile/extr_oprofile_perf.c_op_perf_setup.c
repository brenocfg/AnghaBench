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
typedef  int u32 ;
struct perf_event_attr {int size; int pinned; int /*<<< orphan*/  sample_period; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  event; struct perf_event_attr attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_TYPE_RAW ; 
 TYPE_1__* counter_config ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 int num_counters ; 

__attribute__((used)) static void op_perf_setup(void)
{
	int i;
	u32 size = sizeof(struct perf_event_attr);
	struct perf_event_attr *attr;

	for (i = 0; i < num_counters; ++i) {
		attr = &counter_config[i].attr;
		memset(attr, 0, size);
		attr->type		= PERF_TYPE_RAW;
		attr->size		= size;
		attr->config		= counter_config[i].event;
		attr->sample_period	= counter_config[i].count;
		attr->pinned		= 1;
	}
}