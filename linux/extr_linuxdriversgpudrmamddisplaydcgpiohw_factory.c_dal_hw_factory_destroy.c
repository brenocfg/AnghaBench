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
struct hw_factory {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  kfree (struct hw_factory*) ; 

void dal_hw_factory_destroy(
	struct dc_context *ctx,
	struct hw_factory **factory)
{
	if (!factory || !*factory) {
		BREAK_TO_DEBUGGER();
		return;
	}

	kfree(*factory);

	*factory = NULL;
}