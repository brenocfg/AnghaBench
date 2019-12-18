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
typedef  int /*<<< orphan*/  u32 ;
struct intel_uncore {int dummy; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  mmio_base; struct intel_uncore* uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  RING_CTL (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  RING_HEAD (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  RING_TAIL (int /*<<< orphan*/  const) ; 
 scalar_t__ intel_engine_stop_cs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_uncore_posting_read_fw (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_uncore_read_fw (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void reset_prepare(struct intel_engine_cs *engine)
{
	struct intel_uncore *uncore = engine->uncore;
	const u32 base = engine->mmio_base;

	/*
	 * We stop engines, otherwise we might get failed reset and a
	 * dead gpu (on elk). Also as modern gpu as kbl can suffer
	 * from system hang if batchbuffer is progressing when
	 * the reset is issued, regardless of READY_TO_RESET ack.
	 * Thus assume it is best to stop engines on all gens
	 * where we have a gpu reset.
	 *
	 * WaKBLVECSSemaphoreWaitPoll:kbl (on ALL_ENGINES)
	 *
	 * WaMediaResetMainRingCleanup:ctg,elk (presumably)
	 *
	 * FIXME: Wa for more modern gens needs to be validated
	 */
	GEM_TRACE("%s\n", engine->name);

	if (intel_engine_stop_cs(engine))
		GEM_TRACE("%s: timed out on STOP_RING\n", engine->name);

	intel_uncore_write_fw(uncore,
			      RING_HEAD(base),
			      intel_uncore_read_fw(uncore, RING_TAIL(base)));
	intel_uncore_posting_read_fw(uncore, RING_HEAD(base)); /* paranoia */

	intel_uncore_write_fw(uncore, RING_HEAD(base), 0);
	intel_uncore_write_fw(uncore, RING_TAIL(base), 0);
	intel_uncore_posting_read_fw(uncore, RING_TAIL(base));

	/* The ring must be empty before it is disabled */
	intel_uncore_write_fw(uncore, RING_CTL(base), 0);

	/* Check acts as a post */
	if (intel_uncore_read_fw(uncore, RING_HEAD(base)))
		GEM_TRACE("%s: ring head [%x] not parked\n",
			  engine->name,
			  intel_uncore_read_fw(uncore, RING_HEAD(base)));
}