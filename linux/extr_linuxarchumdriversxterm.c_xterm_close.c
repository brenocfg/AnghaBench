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
struct xterm_chan {int pid; int helper_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_close_file (int) ; 
 int /*<<< orphan*/  os_kill_process (int,int) ; 

__attribute__((used)) static void xterm_close(int fd, void *d)
{
	struct xterm_chan *data = d;

	if (data->pid != -1)
		os_kill_process(data->pid, 1);
	data->pid = -1;

	if (data->helper_pid != -1)
		os_kill_process(data->helper_pid, 0);
	data->helper_pid = -1;

	os_close_file(fd);
}