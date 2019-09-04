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
struct intel_engine_cs {int flags; } ;

/* Variables and functions */
 int I915_ENGINE_NEEDS_CMD_PARSER ; 

__attribute__((used)) static inline bool
intel_engine_needs_cmd_parser(const struct intel_engine_cs *engine)
{
	return engine->flags & I915_ENGINE_NEEDS_CMD_PARSER;
}