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
struct intel_context {int /*<<< orphan*/  engine; int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  __execlists_update_reg_state (struct intel_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void execlists_context_reset(struct intel_context *ce)
{
	/*
	 * Because we emit WA_TAIL_DWORDS there may be a disparity
	 * between our bookkeeping in ce->ring->head and ce->ring->tail and
	 * that stored in context. As we only write new commands from
	 * ce->ring->tail onwards, everything before that is junk. If the GPU
	 * starts reading from its RING_HEAD from the context, it may try to
	 * execute that junk and die.
	 *
	 * The contexts that are stilled pinned on resume belong to the
	 * kernel, and are local to each engine. All other contexts will
	 * have their head/tail sanitized upon pinning before use, so they
	 * will never see garbage,
	 *
	 * So to avoid that we reset the context images upon resume. For
	 * simplicity, we just zero everything out.
	 */
	intel_ring_reset(ce->ring, 0);
	__execlists_update_reg_state(ce, ce->engine);
}