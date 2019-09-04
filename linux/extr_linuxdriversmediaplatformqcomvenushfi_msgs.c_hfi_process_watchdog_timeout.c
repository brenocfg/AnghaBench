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
struct venus_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_SYS_WATCHDOG_TIMEOUT ; 
 int /*<<< orphan*/  event_sys_error (struct venus_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hfi_process_watchdog_timeout(struct venus_core *core)
{
	event_sys_error(core, EVT_SYS_WATCHDOG_TIMEOUT, NULL);
}