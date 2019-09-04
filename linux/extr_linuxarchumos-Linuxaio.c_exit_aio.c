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

/* Variables and functions */
 int aio_pid ; 
 int /*<<< orphan*/  aio_stack ; 
 int /*<<< orphan*/  free_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_kill_process (int,int) ; 

__attribute__((used)) static void exit_aio(void)
{
	if (aio_pid != -1) {
		os_kill_process(aio_pid, 1);
		free_stack(aio_stack, 0);
	}
}