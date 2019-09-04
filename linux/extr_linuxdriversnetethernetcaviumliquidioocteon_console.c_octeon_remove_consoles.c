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
typedef  size_t u32 ;
struct octeon_device {size_t num_consoles; TYPE_1__* console_poll_work; struct octeon_console* console; } ;
struct octeon_console {scalar_t__ output_base_addr; scalar_t__ input_base_addr; scalar_t__ buffer_size; scalar_t__ addr; int /*<<< orphan*/  active; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

void octeon_remove_consoles(struct octeon_device *oct)
{
	u32 i;
	struct octeon_console *console;

	for (i = 0; i < oct->num_consoles; i++) {
		console = &oct->console[i];

		if (!console->active)
			continue;

		cancel_delayed_work_sync(&oct->console_poll_work[i].
						work);
		console->addr = 0;
		console->buffer_size = 0;
		console->input_base_addr = 0;
		console->output_base_addr = 0;
	}

	oct->num_consoles = 0;
}