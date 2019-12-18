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
struct intel_engine_cs {int /*<<< orphan*/  ctx_wa_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_engine_init_ctx_wa (struct intel_engine_cs*,int /*<<< orphan*/ *,char*) ; 

void intel_engine_init_ctx_wa(struct intel_engine_cs *engine)
{
	__intel_engine_init_ctx_wa(engine, &engine->ctx_wa_list, "context");
}