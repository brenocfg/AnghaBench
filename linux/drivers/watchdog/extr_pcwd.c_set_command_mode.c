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
struct TYPE_2__ {int command_mode; int /*<<< orphan*/  io_lock; scalar_t__ io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ISA_IDLE ; 
 scalar_t__ DEBUG ; 
 int ISA_COMMAND_TIMEOUT ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int send_isa_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int set_command_mode(void)
{
	int i, found = 0, count = 0;

	/* Set the card into command mode */
	spin_lock(&pcwd_private.io_lock);
	while ((!found) && (count < 3)) {
		i = send_isa_command(CMD_ISA_IDLE);

		if (i == 0x00)
			found = 1;
		else if (i == 0xF3) {
			/* Card does not like what we've done to it */
			outb_p(0x00, pcwd_private.io_addr + 2);
			udelay(1200);	/* Spec says wait 1ms */
			outb_p(0x00, pcwd_private.io_addr + 2);
			udelay(ISA_COMMAND_TIMEOUT);
		}
		count++;
	}
	spin_unlock(&pcwd_private.io_lock);
	pcwd_private.command_mode = found;

	if (debug >= DEBUG)
		pr_debug("command_mode=%d\n", pcwd_private.command_mode);

	return found;
}