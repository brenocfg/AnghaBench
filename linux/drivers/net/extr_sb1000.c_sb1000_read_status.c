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
 unsigned char inb (int const) ; 

__attribute__((used)) static void
sb1000_read_status(const int ioaddr[], unsigned char in[])
{
	in[1] = inb(ioaddr[0] + 1);
	in[2] = inb(ioaddr[0] + 2);
	in[3] = inb(ioaddr[0] + 3);
	in[4] = inb(ioaddr[0] + 4);
	in[0] = inb(ioaddr[0] + 5);
}