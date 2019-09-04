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
struct slirp_pre_exec_data {int stdin_fd; int stdout_fd; } ;

/* Variables and functions */
 int run_helper (int /*<<< orphan*/ ,struct slirp_pre_exec_data*,char**) ; 
 int /*<<< orphan*/  slirp_pre_exec ; 

__attribute__((used)) static int slirp_tramp(char **argv, int fd)
{
	struct slirp_pre_exec_data pe_data;
	int pid;

	pe_data.stdin_fd = fd;
	pe_data.stdout_fd = fd;
	pid = run_helper(slirp_pre_exec, &pe_data, argv);

	return pid;
}