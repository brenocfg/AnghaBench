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
struct whitelist {int dummy; } ;
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  whitelist_apply (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whitelist_build (struct intel_engine_cs*,struct whitelist*) ; 

void intel_whitelist_workarounds_apply(struct intel_engine_cs *engine)
{
	struct whitelist w;

	whitelist_apply(engine, whitelist_build(engine, &w));
}