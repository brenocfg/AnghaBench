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
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct intel_engine_cs*,int) ;} ;
struct intel_engine_cs {int /*<<< orphan*/  serial; TYPE_1__ reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*,int) ; 

__attribute__((used)) static inline void __intel_engine_reset(struct intel_engine_cs *engine,
					bool stalled)
{
	if (engine->reset.reset)
		engine->reset.reset(engine, stalled);
	engine->serial++; /* contexts lost */
}