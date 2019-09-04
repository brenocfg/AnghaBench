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
struct intel_engine_cs {int /*<<< orphan*/ * unpark; int /*<<< orphan*/ * park; int /*<<< orphan*/  cancel_requests; int /*<<< orphan*/  submit_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_requests ; 
 int /*<<< orphan*/  i9xx_submit_request ; 

__attribute__((used)) static void i9xx_set_default_submission(struct intel_engine_cs *engine)
{
	engine->submit_request = i9xx_submit_request;
	engine->cancel_requests = cancel_requests;

	engine->park = NULL;
	engine->unpark = NULL;
}