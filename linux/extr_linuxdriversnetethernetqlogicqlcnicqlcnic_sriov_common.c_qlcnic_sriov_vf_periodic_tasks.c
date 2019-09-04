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
struct TYPE_2__ {scalar_t__ fnum; } ;
struct qlcnic_adapter {TYPE_1__ fhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  qlcnic_prune_lb_filters (struct qlcnic_adapter*) ; 

__attribute__((used)) static void qlcnic_sriov_vf_periodic_tasks(struct qlcnic_adapter *adapter)
{
	if (adapter->fhash.fnum)
		qlcnic_prune_lb_filters(adapter);
}