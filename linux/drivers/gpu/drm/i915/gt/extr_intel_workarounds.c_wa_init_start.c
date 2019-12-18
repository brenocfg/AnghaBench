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
struct i915_wa_list {char const* name; char const* engine_name; } ;

/* Variables and functions */

__attribute__((used)) static void wa_init_start(struct i915_wa_list *wal, const char *name, const char *engine_name)
{
	wal->name = name;
	wal->engine_name = engine_name;
}