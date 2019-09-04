#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  suspend_state_t ;
struct TYPE_4__ {int suspended; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ AT91_PM_BACKUP ; 
 int /*<<< orphan*/  at91_pm_suspend_in_sram ; 
 int /*<<< orphan*/  at91_pm_suspend_in_sram_sz ; 
 int /*<<< orphan*/  at91_suspend_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_suspend_sram_fn ; 
 int /*<<< orphan*/  cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  fncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outer_resume () ; 
 TYPE_2__* pm_bu ; 
 TYPE_1__ pm_data ; 

__attribute__((used)) static void at91_pm_suspend(suspend_state_t state)
{
	if (pm_data.mode == AT91_PM_BACKUP) {
		pm_bu->suspended = 1;

		cpu_suspend(0, at91_suspend_finish);

		/* The SRAM is lost between suspend cycles */
		at91_suspend_sram_fn = fncpy(at91_suspend_sram_fn,
					     &at91_pm_suspend_in_sram,
					     at91_pm_suspend_in_sram_sz);
	} else {
		at91_suspend_finish(0);
	}

	outer_resume();
}