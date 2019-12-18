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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ I_IXON (struct tty_struct*) ; 
 scalar_t__ L_ECHO (struct tty_struct*) ; 
 int /*<<< orphan*/  commit_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  echo_char (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  isig (int,struct tty_struct*) ; 
 int /*<<< orphan*/  process_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  start_tty (struct tty_struct*) ; 

__attribute__((used)) static void
n_tty_receive_signal_char(struct tty_struct *tty, int signal, unsigned char c)
{
	isig(signal, tty);
	if (I_IXON(tty))
		start_tty(tty);
	if (L_ECHO(tty)) {
		echo_char(c, tty);
		commit_echoes(tty);
	} else
		process_echoes(tty);
	return;
}