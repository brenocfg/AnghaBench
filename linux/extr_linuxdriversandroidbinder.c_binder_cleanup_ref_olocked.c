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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  debug_id; scalar_t__ strong; } ;
struct binder_ref {TYPE_2__* death; TYPE_5__* proc; TYPE_1__ data; TYPE_3__* node; int /*<<< orphan*/  node_entry; int /*<<< orphan*/  rb_node_node; int /*<<< orphan*/  rb_node_desc; } ;
struct TYPE_10__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  refs_by_node; int /*<<< orphan*/  refs_by_desc; } ;
struct TYPE_9__ {int /*<<< orphan*/  debug_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_DEAD_BINDER ; 
 int /*<<< orphan*/  BINDER_DEBUG_INTERNAL_REFS ; 
 int /*<<< orphan*/  BINDER_STAT_DEATH ; 
 int /*<<< orphan*/  BINDER_STAT_REF ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int binder_dec_node_nilocked (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  binder_dequeue_work (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_node_inner_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  binder_node_inner_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  binder_stats_deleted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void binder_cleanup_ref_olocked(struct binder_ref *ref)
{
	bool delete_node = false;

	binder_debug(BINDER_DEBUG_INTERNAL_REFS,
		     "%d delete ref %d desc %d for node %d\n",
		      ref->proc->pid, ref->data.debug_id, ref->data.desc,
		      ref->node->debug_id);

	rb_erase(&ref->rb_node_desc, &ref->proc->refs_by_desc);
	rb_erase(&ref->rb_node_node, &ref->proc->refs_by_node);

	binder_node_inner_lock(ref->node);
	if (ref->data.strong)
		binder_dec_node_nilocked(ref->node, 1, 1);

	hlist_del(&ref->node_entry);
	delete_node = binder_dec_node_nilocked(ref->node, 0, 1);
	binder_node_inner_unlock(ref->node);
	/*
	 * Clear ref->node unless we want the caller to free the node
	 */
	if (!delete_node) {
		/*
		 * The caller uses ref->node to determine
		 * whether the node needs to be freed. Clear
		 * it since the node is still alive.
		 */
		ref->node = NULL;
	}

	if (ref->death) {
		binder_debug(BINDER_DEBUG_DEAD_BINDER,
			     "%d delete ref %d desc %d has death notification\n",
			      ref->proc->pid, ref->data.debug_id,
			      ref->data.desc);
		binder_dequeue_work(ref->proc, &ref->death->work);
		binder_stats_deleted(BINDER_STAT_DEATH);
	}
	binder_stats_deleted(BINDER_STAT_REF);
}