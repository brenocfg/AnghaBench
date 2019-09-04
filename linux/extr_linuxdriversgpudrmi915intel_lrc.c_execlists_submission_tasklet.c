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
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  active; } ;
struct intel_engine_cs {TYPE_4__ timeline; TYPE_3__ execlists; TYPE_2__* i915; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  awake; } ;
struct TYPE_6__ {TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __execlists_submission_tasklet (struct intel_engine_cs* const) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void execlists_submission_tasklet(unsigned long data)
{
	struct intel_engine_cs * const engine = (struct intel_engine_cs *)data;
	unsigned long flags;

	GEM_TRACE("%s awake?=%d, active=%x\n",
		  engine->name,
		  engine->i915->gt.awake,
		  engine->execlists.active);

	spin_lock_irqsave(&engine->timeline.lock, flags);
	__execlists_submission_tasklet(engine);
	spin_unlock_irqrestore(&engine->timeline.lock, flags);
}