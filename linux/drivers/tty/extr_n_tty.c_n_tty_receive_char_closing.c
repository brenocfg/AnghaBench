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
struct tty_struct {int /*<<< orphan*/  flow_stopped; scalar_t__ stopped; } ;

/* Variables and functions */
 unsigned char INTR_CHAR (struct tty_struct*) ; 
 scalar_t__ I_ISTRIP (struct tty_struct*) ; 
 scalar_t__ I_IUCLC (struct tty_struct*) ; 
 scalar_t__ I_IXANY (struct tty_struct*) ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 scalar_t__ L_IEXTEN (struct tty_struct*) ; 
 unsigned char QUIT_CHAR (struct tty_struct*) ; 
 unsigned char START_CHAR (struct tty_struct*) ; 
 unsigned char STOP_CHAR (struct tty_struct*) ; 
 unsigned char SUSP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  process_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  start_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  stop_tty (struct tty_struct*) ; 
 unsigned char tolower (unsigned char) ; 

__attribute__((used)) static void n_tty_receive_char_closing(struct tty_struct *tty, unsigned char c)
{
	if (I_ISTRIP(tty))
		c &= 0x7f;
	if (I_IUCLC(tty) && L_IEXTEN(tty))
		c = tolower(c);

	if (I_IXON(tty)) {
		if (c == STOP_CHAR(tty))
			stop_tty(tty);
		else if (c == START_CHAR(tty) ||
			 (tty->stopped && !tty->flow_stopped && I_IXANY(tty) &&
			  c != INTR_CHAR(tty) && c != QUIT_CHAR(tty) &&
			  c != SUSP_CHAR(tty))) {
			start_tty(tty);
			process_echoes(tty);
		}
	}
}