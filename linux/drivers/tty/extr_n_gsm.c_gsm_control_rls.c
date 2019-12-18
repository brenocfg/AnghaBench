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
typedef  int u8 ;
struct tty_port {int dummy; } ;
struct gsm_mux {TYPE_1__** dlci; } ;
struct TYPE_2__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RLS ; 
 unsigned int NUM_DLCI ; 
 int /*<<< orphan*/  TTY_FRAME ; 
 int /*<<< orphan*/  TTY_OVERRUN ; 
 int /*<<< orphan*/  TTY_PARITY ; 
 int /*<<< orphan*/  gsm_control_reply (struct gsm_mux*,int /*<<< orphan*/ ,int const*,int) ; 
 scalar_t__ gsm_read_ea (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsm_control_rls(struct gsm_mux *gsm, const u8 *data, int clen)
{
	struct tty_port *port;
	unsigned int addr = 0;
	u8 bits;
	int len = clen;
	const u8 *dp = data;

	while (gsm_read_ea(&addr, *dp++) == 0) {
		len--;
		if (len == 0)
			return;
	}
	/* Must be at least one byte following ea */
	len--;
	if (len <= 0)
		return;
	addr >>= 1;
	/* Closed port, or invalid ? */
	if (addr == 0 || addr >= NUM_DLCI || gsm->dlci[addr] == NULL)
		return;
	/* No error ? */
	bits = *dp;
	if ((bits & 1) == 0)
		return;

	port = &gsm->dlci[addr]->port;

	if (bits & 2)
		tty_insert_flip_char(port, 0, TTY_OVERRUN);
	if (bits & 4)
		tty_insert_flip_char(port, 0, TTY_PARITY);
	if (bits & 8)
		tty_insert_flip_char(port, 0, TTY_FRAME);

	tty_flip_buffer_push(port);

	gsm_control_reply(gsm, CMD_RLS, data, clen);
}