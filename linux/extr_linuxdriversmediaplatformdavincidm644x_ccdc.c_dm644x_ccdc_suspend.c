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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccdc_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccdc_save_context () ; 

__attribute__((used)) static int dm644x_ccdc_suspend(struct device *dev)
{
	/* Save CCDC context */
	ccdc_save_context();
	/* Disable CCDC */
	ccdc_enable(0);

	return 0;
}