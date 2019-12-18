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
struct pcips2_data {int /*<<< orphan*/  io; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 scalar_t__ PS2_DATA ; 
 scalar_t__ PS2_STATUS ; 
 unsigned char PS2_STAT_PARITY ; 
 unsigned char PS2_STAT_RXFULL ; 
 unsigned int SERIO_PARITY ; 
 int hweight8 (unsigned char) ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,unsigned char,unsigned int) ; 

__attribute__((used)) static irqreturn_t pcips2_interrupt(int irq, void *devid)
{
	struct pcips2_data *ps2if = devid;
	unsigned char status, scancode;
	int handled = 0;

	do {
		unsigned int flag;

		status = inb(ps2if->base + PS2_STATUS);
		if (!(status & PS2_STAT_RXFULL))
			break;
		handled = 1;
		scancode = inb(ps2if->base + PS2_DATA);
		if (status == 0xff && scancode == 0xff)
			break;

		flag = (status & PS2_STAT_PARITY) ? 0 : SERIO_PARITY;

		if (hweight8(scancode) & 1)
			flag ^= SERIO_PARITY;

		serio_interrupt(ps2if->io, scancode, flag);
	} while (1);
	return IRQ_RETVAL(handled);
}