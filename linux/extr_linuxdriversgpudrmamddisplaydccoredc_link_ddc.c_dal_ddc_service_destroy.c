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
struct ddc_service {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  destruct (struct ddc_service*) ; 
 int /*<<< orphan*/  kfree (struct ddc_service*) ; 

void dal_ddc_service_destroy(struct ddc_service **ddc)
{
	if (!ddc || !*ddc) {
		BREAK_TO_DEBUGGER();
		return;
	}
	destruct(*ddc);
	kfree(*ddc);
	*ddc = NULL;
}