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
struct ktermios {unsigned int c_cflag; int /*<<< orphan*/  c_ispeed; } ;
typedef  int /*<<< orphan*/  speed_t ;

/* Variables and functions */
 unsigned int B0 ; 
 unsigned int BOTHER ; 
 unsigned int CBAUD ; 
 unsigned int CBAUDEX ; 
 unsigned int IBSHIFT ; 
 int /*<<< orphan*/ * baud_table ; 
 unsigned int n_baud_table ; 
 int /*<<< orphan*/  tty_termios_baud_rate (struct ktermios*) ; 

speed_t tty_termios_input_baud_rate(struct ktermios *termios)
{
#ifdef IBSHIFT
	unsigned int cbaud = (termios->c_cflag >> IBSHIFT) & CBAUD;

	if (cbaud == B0)
		return tty_termios_baud_rate(termios);
#ifdef BOTHER
	/* Magic token for arbitrary speed via c_ispeed*/
	if (cbaud == BOTHER)
		return termios->c_ispeed;
#endif
	if (cbaud & CBAUDEX) {
		cbaud &= ~CBAUDEX;

		if (cbaud < 1 || cbaud + 15 > n_baud_table)
			termios->c_cflag &= ~(CBAUDEX << IBSHIFT);
		else
			cbaud += 15;
	}
	return cbaud >= n_baud_table ? 0 : baud_table[cbaud];
#else	/* IBSHIFT */
	return tty_termios_baud_rate(termios);
#endif	/* IBSHIFT */
}