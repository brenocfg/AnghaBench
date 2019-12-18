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
struct wf_pid_param {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  drives_fan ; 
 struct wf_pid_param drives_param ; 
 int /*<<< orphan*/  drives_pid ; 
 int drives_tick ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  wf_control_get_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_control_get_min (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_pid_init (int /*<<< orphan*/ *,struct wf_pid_param*) ; 

__attribute__((used)) static void drives_setup_pid(void)
{
	/* first time initialize things */
	s32 fmin = wf_control_get_min(drives_fan);
	s32 fmax = wf_control_get_max(drives_fan);
	struct wf_pid_param param = drives_param;

	param.min = max(param.min, fmin);
	param.max = min(param.max, fmax);
	wf_pid_init(&drives_pid, &param);
	drives_tick = 1;

	pr_info("wf_pm72: Drive bay control loop started.\n");
}