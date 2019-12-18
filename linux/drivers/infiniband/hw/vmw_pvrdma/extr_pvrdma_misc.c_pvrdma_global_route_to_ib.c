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
struct pvrdma_global_route {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; } ;
struct ib_global_route {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  pvrdma_gid_to_ib (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pvrdma_global_route_to_ib(struct ib_global_route *dst,
			       const struct pvrdma_global_route *src)
{
	pvrdma_gid_to_ib(&dst->dgid, &src->dgid);
	dst->flow_label = src->flow_label;
	dst->sgid_index = src->sgid_index;
	dst->hop_limit = src->hop_limit;
	dst->traffic_class = src->traffic_class;
}