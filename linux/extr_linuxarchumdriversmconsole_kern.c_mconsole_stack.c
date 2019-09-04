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
struct task_struct {int dummy; } ;
struct TYPE_2__ {char* data; } ;
struct mc_request {TYPE_1__ request; } ;

/* Variables and functions */
 struct task_struct* find_task_by_pid_ns (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_pid_ns ; 
 int /*<<< orphan*/  mconsole_reply (struct mc_request*,char*,int,int /*<<< orphan*/ ) ; 
 char* skip_spaces (char*) ; 
 scalar_t__ sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stack_proc ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  with_console (struct mc_request*,int /*<<< orphan*/ ,struct task_struct*) ; 

void mconsole_stack(struct mc_request *req)
{
	char *ptr = req->request.data;
	int pid_requested= -1;
	struct task_struct *to = NULL;

	/*
	 * Would be nice:
	 * 1) Send showregs output to mconsole.
	 * 2) Add a way to stack dump all pids.
	 */

	ptr += strlen("stack");
	ptr = skip_spaces(ptr);

	/*
	 * Should really check for multiple pids or reject bad args here
	 */
	/* What do the arguments in mconsole_reply mean? */
	if (sscanf(ptr, "%d", &pid_requested) == 0) {
		mconsole_reply(req, "Please specify a pid", 1, 0);
		return;
	}

	to = find_task_by_pid_ns(pid_requested, &init_pid_ns);
	if ((to == NULL) || (pid_requested == 0)) {
		mconsole_reply(req, "Couldn't find that pid", 1, 0);
		return;
	}
	with_console(req, stack_proc, to);
}