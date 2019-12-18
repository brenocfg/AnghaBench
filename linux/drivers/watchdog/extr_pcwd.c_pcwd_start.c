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
struct TYPE_2__ {scalar_t__ revision; int /*<<< orphan*/  io_lock; scalar_t__ io_addr; int /*<<< orphan*/  timer; scalar_t__ next_heartbeat; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  ISA_COMMAND_TIMEOUT ; 
 scalar_t__ PCWD_REVISION_C ; 
 scalar_t__ VERBOSE ; 
 scalar_t__ WDT_INTERVAL ; 
 int WD_WDIS ; 
 scalar_t__ debug ; 
 int heartbeat ; 
 int inb_p (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcwd_start(void)
{
	int stat_reg;

	pcwd_private.next_heartbeat = jiffies + (heartbeat * HZ);

	/* Start the timer */
	mod_timer(&pcwd_private.timer, jiffies + WDT_INTERVAL);

	/* Enable the port */
	if (pcwd_private.revision == PCWD_REVISION_C) {
		spin_lock(&pcwd_private.io_lock);
		outb_p(0x00, pcwd_private.io_addr + 3);
		udelay(ISA_COMMAND_TIMEOUT);
		stat_reg = inb_p(pcwd_private.io_addr + 2);
		spin_unlock(&pcwd_private.io_lock);
		if (stat_reg & WD_WDIS) {
			pr_info("Could not start watchdog\n");
			return -EIO;
		}
	}

	if (debug >= VERBOSE)
		pr_debug("Watchdog started\n");

	return 0;
}