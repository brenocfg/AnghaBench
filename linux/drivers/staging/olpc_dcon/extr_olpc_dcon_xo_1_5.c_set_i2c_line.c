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

/* Variables and functions */
 unsigned char inb (int) ; 
 int /*<<< orphan*/  outb (unsigned char,int) ; 

__attribute__((used)) static void set_i2c_line(int sda, int scl)
{
	unsigned char tmp;
	unsigned int port = 0x26;

	/* FIXME: This directly accesses the CRT GPIO controller !!! */
	outb(port, 0x3c4);
	tmp = inb(0x3c5);

	if (scl)
		tmp |= 0x20;
	else
		tmp &= ~0x20;

	if (sda)
		tmp |= 0x10;
	else
		tmp &= ~0x10;

	tmp |= 0x01;

	outb(port, 0x3c4);
	outb(tmp, 0x3c5);
}