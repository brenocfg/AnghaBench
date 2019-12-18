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
 int card_send_command (int const*,char const*,unsigned char const*,unsigned char*) ; 
 int sb1000_end_get_set_command (int const*,char const*) ; 
 int sb1000_start_get_set_command (int const*,char const*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
sb1000_get_PIDs(const int ioaddr[], const char* name, short PID[])
{
	static const unsigned char Command0[6] = {0x80, 0x40, 0x00, 0x00, 0x00, 0x00};
	static const unsigned char Command1[6] = {0x80, 0x41, 0x00, 0x00, 0x00, 0x00};
	static const unsigned char Command2[6] = {0x80, 0x42, 0x00, 0x00, 0x00, 0x00};
	static const unsigned char Command3[6] = {0x80, 0x43, 0x00, 0x00, 0x00, 0x00};

	unsigned char st[7];
	int status;

	udelay(1000);
	if ((status = sb1000_start_get_set_command(ioaddr, name)))
		return status;

	if ((status = card_send_command(ioaddr, name, Command0, st)))
		return status;
	PID[0] = st[1] << 8 | st[2];

	if ((status = card_send_command(ioaddr, name, Command1, st)))
		return status;
	PID[1] = st[1] << 8 | st[2];

	if ((status = card_send_command(ioaddr, name, Command2, st)))
		return status;
	PID[2] = st[1] << 8 | st[2];

	if ((status = card_send_command(ioaddr, name, Command3, st)))
		return status;
	PID[3] = st[1] << 8 | st[2];

	return sb1000_end_get_set_command(ioaddr, name);
}