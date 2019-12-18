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
struct intel_guc_client {int /*<<< orphan*/  wq_lock; } ;
struct intel_guc {struct intel_guc_client* execbuf_client; } ;
struct intel_engine_cs {TYPE_3__* gt; } ;
struct i915_request {TYPE_1__* ring; } ;
struct TYPE_5__ {struct intel_guc guc; } ;
struct TYPE_6__ {TYPE_2__ uc; } ;
struct TYPE_4__ {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_ggtt_writes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guc_add_request (struct intel_guc*,struct i915_request*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void guc_submit(struct intel_engine_cs *engine,
		       struct i915_request **out,
		       struct i915_request **end)
{
	struct intel_guc *guc = &engine->gt->uc.guc;
	struct intel_guc_client *client = guc->execbuf_client;

	spin_lock(&client->wq_lock);

	do {
		struct i915_request *rq = *out++;

		flush_ggtt_writes(rq->ring->vma);
		guc_add_request(guc, rq);
	} while (out != end);

	spin_unlock(&client->wq_lock);
}