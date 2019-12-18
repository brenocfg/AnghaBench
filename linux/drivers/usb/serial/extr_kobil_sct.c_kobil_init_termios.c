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
struct TYPE_2__ {int c_iflag; int /*<<< orphan*/  c_oflag; scalar_t__ c_lflag; } ;
struct tty_struct {TYPE_1__ termios; } ;

/* Variables and functions */
 int ECHO ; 
 int ICANON ; 
 int IEXTEN ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int ISIG ; 
 int IXOFF ; 
 int /*<<< orphan*/  ONLCR ; 
 int XCASE ; 

__attribute__((used)) static void kobil_init_termios(struct tty_struct *tty)
{
	/* Default to echo off and other sane device settings */
	tty->termios.c_lflag = 0;
	tty->termios.c_iflag &= ~(ISIG | ICANON | ECHO | IEXTEN | XCASE);
	tty->termios.c_iflag |= IGNBRK | IGNPAR | IXOFF;
	/* do NOT translate CR to CR-NL (0x0A -> 0x0A 0x0D) */
	tty->termios.c_oflag &= ~ONLCR;
}