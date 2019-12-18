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
struct TYPE_6__ {int /*<<< orphan*/ * timeline; TYPE_4__* ring; struct intel_engine_cs* engine; int /*<<< orphan*/  i915; } ;
struct TYPE_8__ {int vaddr; int size; int effective_size; } ;
struct measure_breadcrumb {int cs; int /*<<< orphan*/  timeline; TYPE_2__ rq; TYPE_4__ ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  vma; } ;
struct intel_engine_cs {int (* emit_fini_breadcrumb ) (TYPE_2__*,int) ;int /*<<< orphan*/  i915; TYPE_1__ status_page; TYPE_3__* gt; } ;
struct TYPE_7__ {int /*<<< orphan*/  scratch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  intel_ring_update_space (TYPE_4__*) ; 
 int /*<<< orphan*/  intel_timeline_fini (int /*<<< orphan*/ *) ; 
 scalar_t__ intel_timeline_init (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int intel_timeline_pin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_timeline_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct measure_breadcrumb*) ; 
 struct measure_breadcrumb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static int measure_breadcrumb_dw(struct intel_engine_cs *engine)
{
	struct measure_breadcrumb *frame;
	int dw = -ENOMEM;

	GEM_BUG_ON(!engine->gt->scratch);

	frame = kzalloc(sizeof(*frame), GFP_KERNEL);
	if (!frame)
		return -ENOMEM;

	if (intel_timeline_init(&frame->timeline,
				engine->gt,
				engine->status_page.vma))
		goto out_frame;

	frame->ring.vaddr = frame->cs;
	frame->ring.size = sizeof(frame->cs);
	frame->ring.effective_size = frame->ring.size;
	intel_ring_update_space(&frame->ring);

	frame->rq.i915 = engine->i915;
	frame->rq.engine = engine;
	frame->rq.ring = &frame->ring;
	frame->rq.timeline = &frame->timeline;

	dw = intel_timeline_pin(&frame->timeline);
	if (dw < 0)
		goto out_timeline;

	dw = engine->emit_fini_breadcrumb(&frame->rq, frame->cs) - frame->cs;
	GEM_BUG_ON(dw & 1); /* RING_TAIL must be qword aligned */

	intel_timeline_unpin(&frame->timeline);

out_timeline:
	intel_timeline_fini(&frame->timeline);
out_frame:
	kfree(frame);
	return dw;
}