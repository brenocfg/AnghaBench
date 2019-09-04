#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_filters {int dummy; } ;
struct TYPE_6__ {struct pt_filters* addr_filters; } ;
struct perf_event {int cpu; TYPE_3__ hw; TYPE_2__* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr_filters; } ;
struct TYPE_5__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PT_CAP_num_address_ranges ; 
 int cpu_to_node (int) ; 
 struct pt_filters* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct pt_filters*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_cap_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pt_addr_filters_init(struct perf_event *event)
{
	struct pt_filters *filters;
	int node = event->cpu == -1 ? -1 : cpu_to_node(event->cpu);

	if (!pt_cap_get(PT_CAP_num_address_ranges))
		return 0;

	filters = kzalloc_node(sizeof(struct pt_filters), GFP_KERNEL, node);
	if (!filters)
		return -ENOMEM;

	if (event->parent)
		memcpy(filters, event->parent->hw.addr_filters,
		       sizeof(*filters));

	event->hw.addr_filters = filters;

	return 0;
}