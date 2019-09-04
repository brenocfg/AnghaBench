#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;
struct i915_request {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; TYPE_2__* ring; int /*<<< orphan*/  emitted_jiffies; int /*<<< orphan*/  global_seqno; TYPE_1__ sched; struct i915_gem_context* gem_context; } ;
struct i915_gem_context {scalar_t__ pid; int /*<<< orphan*/  ban_score; int /*<<< orphan*/  hw_id; } ;
struct drm_i915_error_request {int /*<<< orphan*/  pid; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; int /*<<< orphan*/  start; int /*<<< orphan*/  jiffies; int /*<<< orphan*/  seqno; int /*<<< orphan*/  ban_score; int /*<<< orphan*/  sched_attr; int /*<<< orphan*/  context; } ;
struct TYPE_4__ {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_nr (scalar_t__) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void record_request(struct i915_request *request,
			   struct drm_i915_error_request *erq)
{
	struct i915_gem_context *ctx = request->gem_context;

	erq->context = ctx->hw_id;
	erq->sched_attr = request->sched.attr;
	erq->ban_score = atomic_read(&ctx->ban_score);
	erq->seqno = request->global_seqno;
	erq->jiffies = request->emitted_jiffies;
	erq->start = i915_ggtt_offset(request->ring->vma);
	erq->head = request->head;
	erq->tail = request->tail;

	rcu_read_lock();
	erq->pid = ctx->pid ? pid_nr(ctx->pid) : 0;
	rcu_read_unlock();
}