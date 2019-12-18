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
 int /*<<< orphan*/  intel_engine_set_hwsp_writemask (struct intel_engine_cs*,unsigned int) ; 

__attribute__((used)) static void intel_engine_sanitize_mmio(struct intel_engine_cs *engine)
{
	/* Mask off all writes into the unknown HWSP */
	intel_engine_set_hwsp_writemask(engine, ~0u);
}