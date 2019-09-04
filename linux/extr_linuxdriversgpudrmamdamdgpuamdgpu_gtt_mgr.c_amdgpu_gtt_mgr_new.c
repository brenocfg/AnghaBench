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
struct ttm_place {int flags; scalar_t__ lpfn; scalar_t__ fpfn; } ;
struct ttm_mem_type_manager {struct amdgpu_gtt_mgr* priv; } ;
struct ttm_mem_reg {scalar_t__ mem_type; scalar_t__ num_pages; int /*<<< orphan*/  start; struct amdgpu_gtt_node* mm_node; } ;
struct ttm_buffer_object {struct ttm_mem_reg mem; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  start; } ;
struct amdgpu_gtt_node {TYPE_1__ node; struct ttm_buffer_object* tbo; } ;
struct amdgpu_gtt_mgr {int /*<<< orphan*/  available; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_BO_INVALID_OFFSET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TTM_PL_FLAG_TOPDOWN ; 
 scalar_t__ TTM_PL_TT ; 
 int amdgpu_gtt_mgr_alloc (struct ttm_mem_type_manager*,struct ttm_buffer_object*,struct ttm_place const*,struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  atomic64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_gtt_node*) ; 
 struct amdgpu_gtt_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int amdgpu_gtt_mgr_new(struct ttm_mem_type_manager *man,
			      struct ttm_buffer_object *tbo,
			      const struct ttm_place *place,
			      struct ttm_mem_reg *mem)
{
	struct amdgpu_gtt_mgr *mgr = man->priv;
	struct amdgpu_gtt_node *node;
	int r;

	spin_lock(&mgr->lock);
	if ((&tbo->mem == mem || tbo->mem.mem_type != TTM_PL_TT) &&
	    atomic64_read(&mgr->available) < mem->num_pages) {
		spin_unlock(&mgr->lock);
		return 0;
	}
	atomic64_sub(mem->num_pages, &mgr->available);
	spin_unlock(&mgr->lock);

	node = kzalloc(sizeof(*node), GFP_KERNEL);
	if (!node) {
		r = -ENOMEM;
		goto err_out;
	}

	node->node.start = AMDGPU_BO_INVALID_OFFSET;
	node->node.size = mem->num_pages;
	node->tbo = tbo;
	mem->mm_node = node;

	if (place->fpfn || place->lpfn || place->flags & TTM_PL_FLAG_TOPDOWN) {
		r = amdgpu_gtt_mgr_alloc(man, tbo, place, mem);
		if (unlikely(r)) {
			kfree(node);
			mem->mm_node = NULL;
			r = 0;
			goto err_out;
		}
	} else {
		mem->start = node->node.start;
	}

	return 0;
err_out:
	atomic64_add(mem->num_pages, &mgr->available);

	return r;
}