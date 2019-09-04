#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  seqno; } ;
struct intel_engine_cs {TYPE_1__ timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 intel_engine_last_submit(struct intel_engine_cs *engine)
{
	/* We are only peeking at the tail of the submit queue (and not the
	 * queue itself) in order to gain a hint as to the current active
	 * state of the engine. Callers are not expected to be taking
	 * engine->timeline->lock, nor are they expected to be concerned
	 * wtih serialising this hint with anything, so document it as
	 * a hint and nothing more.
	 */
	return READ_ONCE(engine->timeline.seqno);
}