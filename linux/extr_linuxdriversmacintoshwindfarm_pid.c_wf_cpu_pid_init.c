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
struct wf_cpu_pid_param {int dummy; } ;
struct wf_cpu_pid_state {int first; struct wf_cpu_pid_param param; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct wf_cpu_pid_state*,int /*<<< orphan*/ ,int) ; 

void wf_cpu_pid_init(struct wf_cpu_pid_state *st,
		     struct wf_cpu_pid_param *param)
{
	memset(st, 0, sizeof(struct wf_cpu_pid_state));
	st->param = *param;
	st->first = 1;
}