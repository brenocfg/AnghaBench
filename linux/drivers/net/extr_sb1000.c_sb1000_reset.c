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
 int EIO ; 
 int card_send_command (int const*,char const*,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
sb1000_reset(const int ioaddr[], const char* name)
{
	static const unsigned char Command0[6] = {0x80, 0x16, 0x00, 0x00, 0x00, 0x00};

	unsigned char st[7];
	int port, status;

	port = ioaddr[1] + 6;
	outb(0x4, port);
	inb(port);
	udelay(1000);
	outb(0x0, port);
	inb(port);
	ssleep(1);
	outb(0x4, port);
	inb(port);
	udelay(1000);
	outb(0x0, port);
	inb(port);
	udelay(0);

	if ((status = card_send_command(ioaddr, name, Command0, st)))
		return status;
	if (st[3] != 0xf0)
		return -EIO;
	return 0;
}