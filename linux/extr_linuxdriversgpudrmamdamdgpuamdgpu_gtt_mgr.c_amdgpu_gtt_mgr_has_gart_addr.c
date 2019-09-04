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
struct ttm_mem_reg {struct amdgpu_gtt_node* mm_node; } ;
struct TYPE_2__ {scalar_t__ start; } ;
struct amdgpu_gtt_node {TYPE_1__ node; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_BO_INVALID_OFFSET ; 

bool amdgpu_gtt_mgr_has_gart_addr(struct ttm_mem_reg *mem)
{
	struct amdgpu_gtt_node *node = mem->mm_node;

	return (node->node.start != AMDGPU_BO_INVALID_OFFSET);
}