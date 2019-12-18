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
struct TYPE_2__ {int /*<<< orphan*/  io_lock; scalar_t__ io_addr; } ;

/* Variables and functions */
 scalar_t__ DEBUG ; 
 int PCI_COMMAND_TIMEOUT ; 
 int WD_PCI_WRSP ; 
 scalar_t__ debug ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 TYPE_1__ pcipcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_command(int cmd, int *msb, int *lsb)
{
	int got_response, count;

	if (debug >= DEBUG)
		pr_debug("sending following data cmd=0x%02x msb=0x%02x lsb=0x%02x\n",
			 cmd, *msb, *lsb);

	spin_lock(&pcipcwd_private.io_lock);
	/* If a command requires data it should be written first.
	 * Data for commands with 8 bits of data should be written to port 4.
	 * Commands with 16 bits of data, should be written as LSB to port 4
	 * and MSB to port 5.
	 * After the required data has been written then write the command to
	 * port 6. */
	outb_p(*lsb, pcipcwd_private.io_addr + 4);
	outb_p(*msb, pcipcwd_private.io_addr + 5);
	outb_p(cmd, pcipcwd_private.io_addr + 6);

	/* wait till the pci card processed the command, signaled by
	 * the WRSP bit in port 2 and give it a max. timeout of
	 * PCI_COMMAND_TIMEOUT to process */
	got_response = inb_p(pcipcwd_private.io_addr + 2) & WD_PCI_WRSP;
	for (count = 0; (count < PCI_COMMAND_TIMEOUT) && (!got_response);
								count++) {
		mdelay(1);
		got_response = inb_p(pcipcwd_private.io_addr + 2) & WD_PCI_WRSP;
	}

	if (debug >= DEBUG) {
		if (got_response) {
			pr_debug("time to process command was: %d ms\n",
				 count);
		} else {
			pr_debug("card did not respond on command!\n");
		}
	}

	if (got_response) {
		/* read back response */
		*lsb = inb_p(pcipcwd_private.io_addr + 4);
		*msb = inb_p(pcipcwd_private.io_addr + 5);

		/* clear WRSP bit */
		inb_p(pcipcwd_private.io_addr + 6);

		if (debug >= DEBUG)
			pr_debug("received following data for cmd=0x%02x: msb=0x%02x lsb=0x%02x\n",
				 cmd, *msb, *lsb);
	}

	spin_unlock(&pcipcwd_private.io_lock);

	return got_response;
}