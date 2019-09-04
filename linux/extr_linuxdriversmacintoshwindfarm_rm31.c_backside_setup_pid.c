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
 int /*<<< orphan*/  backside_fan ; 
 struct wf_pid_param backside_param ; 
 int /*<<< orphan*/  backside_pid ; 
 int backside_tick ; 
 struct wf_pid_param dimms_param ; 
 int /*<<< orphan*/  dimms_pid ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  wf_control_get_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_control_get_min (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_pid_init (int /*<<< orphan*/ *,struct wf_pid_param*) ; 

__attribute__((used)) static void backside_setup_pid(void)
{
	/* first time initialize things */
	s32 fmin = wf_control_get_min(backside_fan);
	s32 fmax = wf_control_get_max(backside_fan);
	struct wf_pid_param param;

	param = backside_param;
	param.min = max(param.min, fmin);
	param.max = min(param.max, fmax);
	wf_pid_init(&backside_pid, &param);

	param = dimms_param;
	wf_pid_init(&dimms_pid, &param);

	backside_tick = 1;

	pr_info("wf_rm31: Backside control loop started.\n");
}