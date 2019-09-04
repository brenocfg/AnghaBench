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
struct change_pre_exec_data {int /*<<< orphan*/  stdout_fd; int /*<<< orphan*/  close_me; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void change_pre_exec(void *arg)
{
	struct change_pre_exec_data *data = arg;

	close(data->close_me);
	dup2(data->stdout_fd, 1);
}