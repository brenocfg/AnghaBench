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
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {int /*<<< orphan*/  failed_prepare; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUSPEND_PREPARE ; 
 int dpm_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_save_failed_step (int /*<<< orphan*/ ) ; 
 int dpm_suspend (int /*<<< orphan*/ ) ; 
 TYPE_1__ suspend_stats ; 

int dpm_suspend_start(pm_message_t state)
{
	int error;

	error = dpm_prepare(state);
	if (error) {
		suspend_stats.failed_prepare++;
		dpm_save_failed_step(SUSPEND_PREPARE);
	} else
		error = dpm_suspend(state);
	return error;
}