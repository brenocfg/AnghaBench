#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct list_head {int dummy; } ;
struct TYPE_6__ {struct rb_node* rb_node; } ;
struct TYPE_7__ {TYPE_2__ rb_root; } ;
struct i915_priolist {int priority; struct list_head* requests; int /*<<< orphan*/  used; int /*<<< orphan*/  node; } ;
struct intel_engine_execlists {int no_priolist; TYPE_3__ queue; struct i915_priolist default_priolist; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ active; struct intel_engine_execlists execlists; } ;
struct TYPE_8__ {int /*<<< orphan*/  slab_priorities; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct list_head*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int I915_PRIORITY_COUNT ; 
 int I915_PRIORITY_MASK ; 
 int I915_PRIORITY_NORMAL ; 
 int I915_USER_PRIORITY_SHIFT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  assert_priolists (struct intel_engine_execlists* const) ; 
 TYPE_4__ global ; 
 struct i915_priolist* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_insert_color_cached (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 
 struct i915_priolist* to_priolist (struct rb_node*) ; 
 scalar_t__ unlikely (int) ; 

struct list_head *
i915_sched_lookup_priolist(struct intel_engine_cs *engine, int prio)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct i915_priolist *p;
	struct rb_node **parent, *rb;
	bool first = true;
	int idx, i;

	lockdep_assert_held(&engine->active.lock);
	assert_priolists(execlists);

	/* buckets sorted from highest [in slot 0] to lowest priority */
	idx = I915_PRIORITY_COUNT - (prio & I915_PRIORITY_MASK) - 1;
	prio >>= I915_USER_PRIORITY_SHIFT;
	if (unlikely(execlists->no_priolist))
		prio = I915_PRIORITY_NORMAL;

find_priolist:
	/* most positive priority is scheduled first, equal priorities fifo */
	rb = NULL;
	parent = &execlists->queue.rb_root.rb_node;
	while (*parent) {
		rb = *parent;
		p = to_priolist(rb);
		if (prio > p->priority) {
			parent = &rb->rb_left;
		} else if (prio < p->priority) {
			parent = &rb->rb_right;
			first = false;
		} else {
			goto out;
		}
	}

	if (prio == I915_PRIORITY_NORMAL) {
		p = &execlists->default_priolist;
	} else {
		p = kmem_cache_alloc(global.slab_priorities, GFP_ATOMIC);
		/* Convert an allocation failure to a priority bump */
		if (unlikely(!p)) {
			prio = I915_PRIORITY_NORMAL; /* recurses just once */

			/* To maintain ordering with all rendering, after an
			 * allocation failure we have to disable all scheduling.
			 * Requests will then be executed in fifo, and schedule
			 * will ensure that dependencies are emitted in fifo.
			 * There will be still some reordering with existing
			 * requests, so if userspace lied about their
			 * dependencies that reordering may be visible.
			 */
			execlists->no_priolist = true;
			goto find_priolist;
		}
	}

	p->priority = prio;
	for (i = 0; i < ARRAY_SIZE(p->requests); i++)
		INIT_LIST_HEAD(&p->requests[i]);
	rb_link_node(&p->node, rb, parent);
	rb_insert_color_cached(&p->node, &execlists->queue, first);
	p->used = 0;

out:
	p->used |= BIT(idx);
	return &p->requests[idx];
}