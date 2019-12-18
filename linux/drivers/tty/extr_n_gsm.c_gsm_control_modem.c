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
struct gsm_mux {struct gsm_dlci** dlci; } ;
struct gsm_dlci {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MSC ; 
 unsigned int NUM_DLCI ; 
 int /*<<< orphan*/  gsm_control_reply (struct gsm_mux*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  gsm_process_modem (struct tty_struct*,struct gsm_dlci*,unsigned int,int) ; 
 scalar_t__ gsm_read_ea (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void gsm_control_modem(struct gsm_mux *gsm, const u8 *data, int clen)
{
	unsigned int addr = 0;
	unsigned int modem = 0;
	unsigned int brk = 0;
	struct gsm_dlci *dlci;
	int len = clen;
	const u8 *dp = data;
	struct tty_struct *tty;

	while (gsm_read_ea(&addr, *dp++) == 0) {
		len--;
		if (len == 0)
			return;
	}
	/* Must be at least one byte following the EA */
	len--;
	if (len <= 0)
		return;

	addr >>= 1;
	/* Closed port, or invalid ? */
	if (addr == 0 || addr >= NUM_DLCI || gsm->dlci[addr] == NULL)
		return;
	dlci = gsm->dlci[addr];

	while (gsm_read_ea(&modem, *dp++) == 0) {
		len--;
		if (len == 0)
			return;
	}
	len--;
	if (len > 0) {
		while (gsm_read_ea(&brk, *dp++) == 0) {
			len--;
			if (len == 0)
				return;
		}
		modem <<= 7;
		modem |= (brk & 0x7f);
	}
	tty = tty_port_tty_get(&dlci->port);
	gsm_process_modem(tty, dlci, modem, clen);
	if (tty) {
		tty_wakeup(tty);
		tty_kref_put(tty);
	}
	gsm_control_reply(gsm, CMD_MSC, data, clen);
}