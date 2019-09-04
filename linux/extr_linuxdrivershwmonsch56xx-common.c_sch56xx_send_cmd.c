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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int EIO ; 
 int SCH56XX_CMD_READ ; 
 int SCH56XX_CMD_WRITE ; 
 int inb (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,int) ; 

__attribute__((used)) static int sch56xx_send_cmd(u16 addr, u8 cmd, u16 reg, u8 v)
{
	u8 val;
	int i;
	/*
	 * According to SMSC for the commands we use the maximum time for
	 * the EM to respond is 15 ms, but testing shows in practice it
	 * responds within 15-32 reads, so we first busy poll, and if
	 * that fails sleep a bit and try again until we are way past
	 * the 15 ms maximum response time.
	 */
	const int max_busy_polls = 64;
	const int max_lazy_polls = 32;

	/* (Optional) Write-Clear the EC to Host Mailbox Register */
	val = inb(addr + 1);
	outb(val, addr + 1);

	/* Set Mailbox Address Pointer to first location in Region 1 */
	outb(0x00, addr + 2);
	outb(0x80, addr + 3);

	/* Write Request Packet Header */
	outb(cmd, addr + 4); /* VREG Access Type read:0x02 write:0x03 */
	outb(0x01, addr + 5); /* # of Entries: 1 Byte (8-bit) */
	outb(0x04, addr + 2); /* Mailbox AP to first data entry loc. */

	/* Write Value field */
	if (cmd == SCH56XX_CMD_WRITE)
		outb(v, addr + 4);

	/* Write Address field */
	outb(reg & 0xff, addr + 6);
	outb(reg >> 8, addr + 7);

	/* Execute the Random Access Command */
	outb(0x01, addr); /* Write 01h to the Host-to-EC register */

	/* EM Interface Polling "Algorithm" */
	for (i = 0; i < max_busy_polls + max_lazy_polls; i++) {
		if (i >= max_busy_polls)
			msleep(1);
		/* Read Interrupt source Register */
		val = inb(addr + 8);
		/* Write Clear the interrupt source bits */
		if (val)
			outb(val, addr + 8);
		/* Command Completed ? */
		if (val & 0x01)
			break;
	}
	if (i == max_busy_polls + max_lazy_polls) {
		pr_err("Max retries exceeded reading virtual register 0x%04hx (%d)\n",
		       reg, 1);
		return -EIO;
	}

	/*
	 * According to SMSC we may need to retry this, but sofar I've always
	 * seen this succeed in 1 try.
	 */
	for (i = 0; i < max_busy_polls; i++) {
		/* Read EC-to-Host Register */
		val = inb(addr + 1);
		/* Command Completed ? */
		if (val == 0x01)
			break;

		if (i == 0)
			pr_warn("EC reports: 0x%02x reading virtual register 0x%04hx\n",
				(unsigned int)val, reg);
	}
	if (i == max_busy_polls) {
		pr_err("Max retries exceeded reading virtual register 0x%04hx (%d)\n",
		       reg, 2);
		return -EIO;
	}

	/*
	 * According to the SMSC app note we should now do:
	 *
	 * Set Mailbox Address Pointer to first location in Region 1 *
	 * outb(0x00, addr + 2);
	 * outb(0x80, addr + 3);
	 *
	 * But if we do that things don't work, so let's not.
	 */

	/* Read Value field */
	if (cmd == SCH56XX_CMD_READ)
		return inb(addr + 4);

	return 0;
}