#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct psp_xgmi_topology_info {int num_nodes; TYPE_5__* nodes; } ;
struct TYPE_8__ {scalar_t__ node_id; } ;
struct TYPE_9__ {TYPE_3__ xgmi; } ;
struct TYPE_6__ {struct psp_xgmi_topology_info top_info; } ;
struct TYPE_7__ {TYPE_1__ xgmi_context; } ;
struct amdgpu_device {TYPE_4__ gmc; TYPE_2__ psp; } ;
struct TYPE_10__ {scalar_t__ node_id; int num_hops; } ;

/* Variables and functions */
 int EINVAL ; 

int amdgpu_xgmi_get_hops_count(struct amdgpu_device *adev,
		struct amdgpu_device *peer_adev)
{
	struct psp_xgmi_topology_info *top = &adev->psp.xgmi_context.top_info;
	int i;

	for (i = 0 ; i < top->num_nodes; ++i)
		if (top->nodes[i].node_id == peer_adev->gmc.xgmi.node_id)
			return top->nodes[i].num_hops;
	return	-EINVAL;
}