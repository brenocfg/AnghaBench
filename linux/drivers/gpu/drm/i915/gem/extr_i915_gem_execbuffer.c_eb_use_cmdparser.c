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
struct i915_execbuffer {TYPE_1__* args; int /*<<< orphan*/  engine; } ;
struct TYPE_2__ {scalar_t__ batch_len; } ;

/* Variables and functions */
 scalar_t__ intel_engine_requires_cmd_parser (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_engine_using_cmd_parser (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool eb_use_cmdparser(const struct i915_execbuffer *eb)
{
	return intel_engine_requires_cmd_parser(eb->engine) ||
		(intel_engine_using_cmd_parser(eb->engine) &&
		 eb->args->batch_len);
}