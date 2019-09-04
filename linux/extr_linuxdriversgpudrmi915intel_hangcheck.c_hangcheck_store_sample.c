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
struct intel_engine_hangcheck {int /*<<< orphan*/  wedged; int /*<<< orphan*/  stalled; int /*<<< orphan*/  action; int /*<<< orphan*/  seqno; int /*<<< orphan*/  acthd; } ;
struct TYPE_2__ {int /*<<< orphan*/  wedged; int /*<<< orphan*/  stalled; int /*<<< orphan*/  action; int /*<<< orphan*/  seqno; int /*<<< orphan*/  acthd; } ;
struct intel_engine_cs {TYPE_1__ hangcheck; } ;

/* Variables and functions */

__attribute__((used)) static void hangcheck_store_sample(struct intel_engine_cs *engine,
				   const struct intel_engine_hangcheck *hc)
{
	engine->hangcheck.acthd = hc->acthd;
	engine->hangcheck.seqno = hc->seqno;
	engine->hangcheck.action = hc->action;
	engine->hangcheck.stalled = hc->stalled;
	engine->hangcheck.wedged = hc->wedged;
}