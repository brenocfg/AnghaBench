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
struct intel_engine_cs {int /*<<< orphan*/  submit_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen6_bsd_submit_request ; 
 int /*<<< orphan*/  i9xx_set_default_submission (struct intel_engine_cs*) ; 

__attribute__((used)) static void gen6_bsd_set_default_submission(struct intel_engine_cs *engine)
{
	i9xx_set_default_submission(engine);
	engine->submit_request = gen6_bsd_submit_request;
}