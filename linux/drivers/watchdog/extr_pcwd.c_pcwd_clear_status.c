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
struct TYPE_2__ {scalar_t__ revision; int /*<<< orphan*/  io_lock; scalar_t__ io_addr; } ;

/* Variables and functions */
 scalar_t__ DEBUG ; 
 scalar_t__ PCWD_REVISION_C ; 
 scalar_t__ VERBOSE ; 
 int WD_REVC_R2DS ; 
 scalar_t__ debug ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcwd_clear_status(void)
{
	int control_status;

	if (pcwd_private.revision == PCWD_REVISION_C) {
		spin_lock(&pcwd_private.io_lock);

		if (debug >= VERBOSE)
			pr_info("clearing watchdog trip status\n");

		control_status = inb_p(pcwd_private.io_addr + 1);

		if (debug >= DEBUG) {
			pr_debug("status was: 0x%02x\n", control_status);
			pr_debug("sending: 0x%02x\n",
				 (control_status & WD_REVC_R2DS));
		}

		/* clear reset status & Keep Relay 2 disable state as it is */
		outb_p((control_status & WD_REVC_R2DS),
						pcwd_private.io_addr + 1);

		spin_unlock(&pcwd_private.io_lock);
	}
	return 0;
}