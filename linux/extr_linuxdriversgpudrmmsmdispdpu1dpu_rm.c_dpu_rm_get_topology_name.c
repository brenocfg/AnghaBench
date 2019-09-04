#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msm_display_topology {int dummy; } ;
typedef  enum dpu_rm_topology_name { ____Placeholder_dpu_rm_topology_name } dpu_rm_topology_name ;
struct TYPE_3__ {int top_name; } ;

/* Variables and functions */
 int DPU_RM_TOPOLOGY_MAX ; 
 int DPU_RM_TOPOLOGY_NONE ; 
 scalar_t__ RM_IS_TOPOLOGY_MATCH (TYPE_1__,struct msm_display_topology) ; 
 TYPE_1__* g_top_table ; 

enum dpu_rm_topology_name
dpu_rm_get_topology_name(struct msm_display_topology topology)
{
	int i;

	for (i = 0; i < DPU_RM_TOPOLOGY_MAX; i++)
		if (RM_IS_TOPOLOGY_MATCH(g_top_table[i], topology))
			return g_top_table[i].top_name;

	return DPU_RM_TOPOLOGY_NONE;
}