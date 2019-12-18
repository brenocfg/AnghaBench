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
struct intel_engine_cs {int dummy; } ;
struct hangcheck {void* head; void* ring; int /*<<< orphan*/  acthd; } ;

/* Variables and functions */
 void* ENGINE_READ (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_HEAD ; 
 int /*<<< orphan*/  RING_START ; 
 int /*<<< orphan*/  intel_engine_get_active_head (struct intel_engine_cs*) ; 

__attribute__((used)) static void hangcheck_load_sample(struct intel_engine_cs *engine,
				  struct hangcheck *hc)
{
	hc->acthd = intel_engine_get_active_head(engine);
	hc->ring = ENGINE_READ(engine, RING_START);
	hc->head = ENGINE_READ(engine, RING_HEAD);
}