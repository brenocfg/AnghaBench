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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pending; } ;
struct intel_engine_cs {TYPE_2__ active; TYPE_1__ execlists; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __execlists_submission_tasklet (struct intel_engine_cs* const) ; 
 int /*<<< orphan*/  process_csb (struct intel_engine_cs* const) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void execlists_submission_tasklet(unsigned long data)
{
	struct intel_engine_cs * const engine = (struct intel_engine_cs *)data;
	unsigned long flags;

	process_csb(engine);
	if (!READ_ONCE(engine->execlists.pending[0])) {
		spin_lock_irqsave(&engine->active.lock, flags);
		__execlists_submission_tasklet(engine);
		spin_unlock_irqrestore(&engine->active.lock, flags);
	}
}