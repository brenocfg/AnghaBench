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
struct cc_fips_handle {int /*<<< orphan*/  tasklet; } ;
struct cc_drvdata {scalar_t__ hw_rev; struct cc_fips_handle* fips_handle; } ;

/* Variables and functions */
 scalar_t__ CC_HW_REV_712 ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void fips_handler(struct cc_drvdata *drvdata)
{
	struct cc_fips_handle *fips_handle_ptr = drvdata->fips_handle;

	if (drvdata->hw_rev < CC_HW_REV_712)
		return;

	tasklet_schedule(&fips_handle_ptr->tasklet);
}