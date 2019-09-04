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

/* Variables and functions */
 int /*<<< orphan*/  channel_subsystem_reinit () ; 
 int /*<<< orphan*/  lgr_info_log () ; 
 int /*<<< orphan*/  zpci_rescan () ; 

void s390_early_resume(void)
{
	lgr_info_log();
	channel_subsystem_reinit();
	zpci_rescan();
}