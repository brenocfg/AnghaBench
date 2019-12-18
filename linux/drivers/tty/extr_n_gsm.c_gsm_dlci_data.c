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
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {int dummy; } ;
struct tty_port {int dummy; } ;
struct gsm_dlci {int adaption; struct tty_port port; } ;

/* Variables and functions */
 int debug ; 
 int /*<<< orphan*/  gsm_process_modem (struct tty_struct*,struct gsm_dlci*,unsigned int,int) ; 
 int /*<<< orphan*/  gsm_read_ea (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_port*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (struct tty_port*) ; 

__attribute__((used)) static void gsm_dlci_data(struct gsm_dlci *dlci, const u8 *data, int clen)
{
	/* krefs .. */
	struct tty_port *port = &dlci->port;
	struct tty_struct *tty;
	unsigned int modem = 0;
	int len = clen;

	if (debug & 16)
		pr_debug("%d bytes for tty\n", len);
	switch (dlci->adaption)  {
	/* Unsupported types */
	case 4:		/* Packetised interruptible data */
		break;
	case 3:		/* Packetised uininterruptible voice/data */
		break;
	case 2:		/* Asynchronous serial with line state in each frame */
		while (gsm_read_ea(&modem, *data++) == 0) {
			len--;
			if (len == 0)
				return;
		}
		tty = tty_port_tty_get(port);
		if (tty) {
			gsm_process_modem(tty, dlci, modem, clen);
			tty_kref_put(tty);
		}
		/* Fall through */
	case 1:		/* Line state will go via DLCI 0 controls only */
	default:
		tty_insert_flip_string(port, data, len);
		tty_flip_buffer_push(port);
	}
}