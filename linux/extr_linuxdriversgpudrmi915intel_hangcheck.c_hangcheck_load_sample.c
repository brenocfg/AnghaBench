#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_engine_hangcheck {int /*<<< orphan*/  seqno; int /*<<< orphan*/  acthd; } ;
struct intel_engine_cs {int /*<<< orphan*/  (* irq_seqno_barrier ) (struct intel_engine_cs*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  intel_engine_get_active_head (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 

__attribute__((used)) static void hangcheck_load_sample(struct intel_engine_cs *engine,
				  struct intel_engine_hangcheck *hc)
{
	/* We don't strictly need an irq-barrier here, as we are not
	 * serving an interrupt request, be paranoid in case the
	 * barrier has side-effects (such as preventing a broken
	 * cacheline snoop) and so be sure that we can see the seqno
	 * advance. If the seqno should stick, due to a stale
	 * cacheline, we would erroneously declare the GPU hung.
	 */
	if (engine->irq_seqno_barrier)
		engine->irq_seqno_barrier(engine);

	hc->acthd = intel_engine_get_active_head(engine);
	hc->seqno = intel_engine_get_seqno(engine);
}