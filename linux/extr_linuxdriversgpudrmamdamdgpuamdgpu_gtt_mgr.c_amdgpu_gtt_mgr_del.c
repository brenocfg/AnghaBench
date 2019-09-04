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
struct ttm_mem_type_manager {struct amdgpu_gtt_mgr* priv; } ;
struct ttm_mem_reg {struct amdgpu_gtt_node* mm_node; int /*<<< orphan*/  num_pages; } ;
struct TYPE_2__ {scalar_t__ start; } ;
struct amdgpu_gtt_node {TYPE_1__ node; } ;
struct amdgpu_gtt_mgr {int /*<<< orphan*/  available; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_BO_INVALID_OFFSET ; 
 int /*<<< orphan*/  atomic64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_remove_node (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_gtt_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_gtt_mgr_del(struct ttm_mem_type_manager *man,
			       struct ttm_mem_reg *mem)
{
	struct amdgpu_gtt_mgr *mgr = man->priv;
	struct amdgpu_gtt_node *node = mem->mm_node;

	if (!node)
		return;

	spin_lock(&mgr->lock);
	if (node->node.start != AMDGPU_BO_INVALID_OFFSET)
		drm_mm_remove_node(&node->node);
	spin_unlock(&mgr->lock);
	atomic64_add(mem->num_pages, &mgr->available);

	kfree(node);
	mem->mm_node = NULL;
}