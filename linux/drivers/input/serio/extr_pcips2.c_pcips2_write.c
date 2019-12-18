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
struct serio {struct pcips2_data* port_data; } ;
struct pcips2_data {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PS2_DATA ; 
 scalar_t__ PS2_STATUS ; 
 unsigned int PS2_STAT_TXEMPTY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static int pcips2_write(struct serio *io, unsigned char val)
{
	struct pcips2_data *ps2if = io->port_data;
	unsigned int stat;

	do {
		stat = inb(ps2if->base + PS2_STATUS);
		cpu_relax();
	} while (!(stat & PS2_STAT_TXEMPTY));

	outb(val, ps2if->base + PS2_DATA);

	return 0;
}