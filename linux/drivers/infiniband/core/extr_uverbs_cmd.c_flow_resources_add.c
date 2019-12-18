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
struct ib_uflow_resources {scalar_t__ num; scalar_t__ max; int /*<<< orphan*/  counters_num; struct ib_counters** counters; int /*<<< orphan*/  collection_num; struct ib_flow_action** collection; } ;
struct ib_flow_action {int /*<<< orphan*/  usecnt; } ;
struct ib_counters {int /*<<< orphan*/  usecnt; } ;
typedef  enum ib_flow_spec_type { ____Placeholder_ib_flow_spec_type } ib_flow_spec_type ;

/* Variables and functions */
#define  IB_FLOW_SPEC_ACTION_COUNT 129 
#define  IB_FLOW_SPEC_ACTION_HANDLE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

void flow_resources_add(struct ib_uflow_resources *uflow_res,
			enum ib_flow_spec_type type,
			void *ibobj)
{
	WARN_ON(uflow_res->num >= uflow_res->max);

	switch (type) {
	case IB_FLOW_SPEC_ACTION_HANDLE:
		atomic_inc(&((struct ib_flow_action *)ibobj)->usecnt);
		uflow_res->collection[uflow_res->collection_num++] =
			(struct ib_flow_action *)ibobj;
		break;
	case IB_FLOW_SPEC_ACTION_COUNT:
		atomic_inc(&((struct ib_counters *)ibobj)->usecnt);
		uflow_res->counters[uflow_res->counters_num++] =
			(struct ib_counters *)ibobj;
		break;
	default:
		WARN_ON(1);
	}

	uflow_res->num++;
}