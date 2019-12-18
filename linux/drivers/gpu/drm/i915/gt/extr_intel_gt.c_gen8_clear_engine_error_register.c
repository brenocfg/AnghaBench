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

/* Variables and functions */
 int /*<<< orphan*/  GEN6_RING_FAULT_REG_POSTING_READ (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  GEN6_RING_FAULT_REG_RMW (struct intel_engine_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_FAULT_VALID ; 

__attribute__((used)) static void gen8_clear_engine_error_register(struct intel_engine_cs *engine)
{
	GEN6_RING_FAULT_REG_RMW(engine, RING_FAULT_VALID, 0);
	GEN6_RING_FAULT_REG_POSTING_READ(engine);
}