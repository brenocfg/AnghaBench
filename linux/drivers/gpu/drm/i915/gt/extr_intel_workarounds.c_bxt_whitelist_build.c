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
struct intel_engine_cs {scalar_t__ class; int /*<<< orphan*/  whitelist; } ;

/* Variables and functions */
 scalar_t__ RENDER_CLASS ; 
 int /*<<< orphan*/  gen9_whitelist_build (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bxt_whitelist_build(struct intel_engine_cs *engine)
{
	if (engine->class != RENDER_CLASS)
		return;

	gen9_whitelist_build(&engine->whitelist);
}