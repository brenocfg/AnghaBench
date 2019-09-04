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
struct cc6_settings {int /*<<< orphan*/  cpu_pstate_separation_time; int /*<<< orphan*/  nb_pstate_switch_disable; int /*<<< orphan*/  cpu_pstate_disable; int /*<<< orphan*/  cpu_cc6_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_DBG_LOG (char*,...) ; 

__attribute__((used)) static void smu8_hw_print_display_cfg(
	const struct cc6_settings *cc6_settings)
{
	PP_DBG_LOG("New Display Configuration:\n");

	PP_DBG_LOG("   cpu_cc6_disable: %d\n",
			cc6_settings->cpu_cc6_disable);
	PP_DBG_LOG("   cpu_pstate_disable: %d\n",
			cc6_settings->cpu_pstate_disable);
	PP_DBG_LOG("   nb_pstate_switch_disable: %d\n",
			cc6_settings->nb_pstate_switch_disable);
	PP_DBG_LOG("   cpu_pstate_separation_time: %d\n\n",
			cc6_settings->cpu_pstate_separation_time);
}