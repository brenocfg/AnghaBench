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
struct TYPE_2__ {int /*<<< orphan*/  last_head; int /*<<< orphan*/  last_ring; int /*<<< orphan*/  acthd; } ;
struct intel_engine_cs {TYPE_1__ hangcheck; } ;
struct hangcheck {int /*<<< orphan*/  head; int /*<<< orphan*/  ring; int /*<<< orphan*/  acthd; } ;

/* Variables and functions */

__attribute__((used)) static void hangcheck_store_sample(struct intel_engine_cs *engine,
				   const struct hangcheck *hc)
{
	engine->hangcheck.acthd = hc->acthd;
	engine->hangcheck.last_ring = hc->ring;
	engine->hangcheck.last_head = hc->head;
}