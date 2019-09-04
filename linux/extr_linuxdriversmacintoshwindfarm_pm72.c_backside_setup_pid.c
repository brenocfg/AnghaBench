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
typedef  int u32 ;
struct wf_pid_param {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  backside_fan ; 
 int /*<<< orphan*/  backside_pid ; 
 int backside_tick ; 
 struct wf_pid_param backside_u3_param ; 
 struct wf_pid_param backside_u3h_param ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
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
	struct device_node *u3;
	int u3h = 1; /* conservative by default */

	u3 = of_find_node_by_path("/u3@0,f8000000");
	if (u3 != NULL) {
		const u32 *vers = of_get_property(u3, "device-rev", NULL);
		if (vers)
			if (((*vers) & 0x3f) < 0x34)
				u3h = 0;
		of_node_put(u3);
	}

	param = u3h ? backside_u3h_param : backside_u3_param;

	param.min = max(param.min, fmin);
	param.max = min(param.max, fmax);
	wf_pid_init(&backside_pid, &param);
	backside_tick = 1;

	pr_info("wf_pm72: Backside control loop started.\n");
}