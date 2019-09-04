#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct TYPE_4__ {struct rb_node* rb_node; } ;
struct TYPE_6__ {TYPE_1__ rb_root; } ;
struct i915_priolist {int priority; int /*<<< orphan*/  node; int /*<<< orphan*/  requests; } ;
struct intel_engine_execlists {int no_priolist; TYPE_3__ queue; struct i915_priolist default_priolist; } ;
struct intel_engine_cs {TYPE_2__* i915; struct intel_engine_execlists execlists; } ;
struct TYPE_5__ {int /*<<< orphan*/  priorities; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int I915_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct i915_priolist* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_insert_color_cached (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 
 struct i915_priolist* to_priolist (struct rb_node*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct i915_priolist *
lookup_priolist(struct intel_engine_cs *engine, int prio)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct i915_priolist *p;
	struct rb_node **parent, *rb;
	bool first = true;

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
			return p;
		}
	}

	if (prio == I915_PRIORITY_NORMAL) {
		p = &execlists->default_priolist;
	} else {
		p = kmem_cache_alloc(engine->i915->priorities, GFP_ATOMIC);
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
	INIT_LIST_HEAD(&p->requests);
	rb_link_node(&p->node, rb, parent);
	rb_insert_color_cached(&p->node, &execlists->queue, first);

	return p;
}