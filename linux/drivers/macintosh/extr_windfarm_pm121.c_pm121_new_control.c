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
struct wf_control {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ ; 
 int /*<<< orphan*/  FAN_CPU ; 
 int /*<<< orphan*/  FAN_HD ; 
 int /*<<< orphan*/  FAN_OD ; 
 int pm121_all_controls_ok ; 
 scalar_t__ pm121_register_control (struct wf_control*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm121_new_control(struct wf_control *ct)
{
	int all = 1;

	if (pm121_all_controls_ok)
		return;

	all = pm121_register_control(ct, "optical-drive-fan", FAN_OD) && all;
	all = pm121_register_control(ct, "hard-drive-fan", FAN_HD) && all;
	all = pm121_register_control(ct, "cpu-fan", FAN_CPU) && all;
	all = pm121_register_control(ct, "cpufreq-clamp", CPUFREQ) && all;

	if (all)
		pm121_all_controls_ok = 1;
}