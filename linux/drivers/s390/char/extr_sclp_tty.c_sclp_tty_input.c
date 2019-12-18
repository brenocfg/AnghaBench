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
#define  CTRLCHAR_CTRL 130 
 unsigned int CTRLCHAR_MASK ; 
#define  CTRLCHAR_NONE 129 
#define  CTRLCHAR_SYSRQ 128 
 int /*<<< orphan*/  TTY_NORMAL ; 
 unsigned int ctrlchar_handle (unsigned char*,unsigned int,struct tty_struct*) ; 
 int /*<<< orphan*/  sclp_port ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sclp_tty_input(unsigned char* buf, unsigned int count)
{
	struct tty_struct *tty = tty_port_tty_get(&sclp_port);
	unsigned int cchar;

	/*
	 * If this tty driver is currently closed
	 * then throw the received input away.
	 */
	if (tty == NULL)
		return;
	cchar = ctrlchar_handle(buf, count, tty);
	switch (cchar & CTRLCHAR_MASK) {
	case CTRLCHAR_SYSRQ:
		break;
	case CTRLCHAR_CTRL:
		tty_insert_flip_char(&sclp_port, cchar, TTY_NORMAL);
		tty_flip_buffer_push(&sclp_port);
		break;
	case CTRLCHAR_NONE:
		/* send (normal) input to line discipline */
		if (count < 2 ||
		    (strncmp((const char *) buf + count - 2, "^n", 2) &&
		     strncmp((const char *) buf + count - 2, "\252n", 2))) {
			/* add the auto \n */
			tty_insert_flip_string(&sclp_port, buf, count);
			tty_insert_flip_char(&sclp_port, '\n', TTY_NORMAL);
		} else
			tty_insert_flip_string(&sclp_port, buf, count - 2);
		tty_flip_buffer_push(&sclp_port);
		break;
	}
	tty_kref_put(tty);
}