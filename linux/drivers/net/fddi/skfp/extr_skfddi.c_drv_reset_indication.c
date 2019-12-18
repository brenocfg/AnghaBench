#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ResetRequested; } ;
struct s_smc {TYPE_1__ os; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void drv_reset_indication(struct s_smc *smc)
{
	pr_debug("entering drv_reset_indication\n");

	smc->os.ResetRequested = TRUE;	// Set flag.

}