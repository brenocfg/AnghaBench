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
struct octeon_device {struct octeon_console* console; } ;
struct octeon_console {scalar_t__ waiting; } ;

/* Variables and functions */

__attribute__((used)) static void octeon_console_handle_result(struct octeon_device *oct,
					 size_t console_num)
{
	struct octeon_console *console;

	console = &oct->console[console_num];

	console->waiting = 0;
}