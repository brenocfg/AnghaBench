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
 int /*<<< orphan*/  fini_hash_table (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_using_cmd_parser (struct intel_engine_cs*) ; 

void intel_engine_cleanup_cmd_parser(struct intel_engine_cs *engine)
{
	if (!intel_engine_using_cmd_parser(engine))
		return;

	fini_hash_table(engine);
}