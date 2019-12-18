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
typedef  int tcflag_t ;
struct ktermios {int c_cflag; } ;

/* Variables and functions */
#define  CS5 130 
#define  CS6 129 
#define  CS7 128 
 int CSIZE ; 

__attribute__((used)) static unsigned int stm32_get_databits(struct ktermios *termios)
{
	unsigned int bits;

	tcflag_t cflag = termios->c_cflag;

	switch (cflag & CSIZE) {
	/*
	 * CSIZE settings are not necessarily supported in hardware.
	 * CSIZE unsupported configurations are handled here to set word length
	 * to 8 bits word as default configuration and to print debug message.
	 */
	case CS5:
		bits = 5;
		break;
	case CS6:
		bits = 6;
		break;
	case CS7:
		bits = 7;
		break;
	/* default including CS8 */
	default:
		bits = 8;
		break;
	}

	return bits;
}