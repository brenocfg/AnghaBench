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
struct comedi_8254 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i8254_write (struct comedi_8254*,unsigned int,unsigned int) ; 

void comedi_8254_write(struct comedi_8254 *i8254,
		       unsigned int counter, unsigned int val)
{
	unsigned int byte;

	if (counter > 2)
		return;
	if (val > 0xffff)
		return;

	/* load LSB then MSB */
	byte = val & 0xff;
	__i8254_write(i8254, byte, counter);
	byte = (val >> 8) & 0xff;
	__i8254_write(i8254, byte, counter);
}