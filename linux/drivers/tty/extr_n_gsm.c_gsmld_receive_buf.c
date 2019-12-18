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
struct tty_struct {struct gsm_mux* disc_data; } ;
struct gsm_mux {int /*<<< orphan*/  (* error ) (struct gsm_mux*,unsigned char const,char) ;int /*<<< orphan*/  (* receive ) (struct gsm_mux*,unsigned char const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
#define  TTY_BREAK 132 
#define  TTY_FRAME 131 
#define  TTY_NORMAL 130 
#define  TTY_OVERRUN 129 
#define  TTY_PARITY 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,char) ; 
 int debug ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub1 (struct gsm_mux*,unsigned char const) ; 
 int /*<<< orphan*/  stub2 (struct gsm_mux*,unsigned char const,char) ; 
 int /*<<< orphan*/  tty_name (struct tty_struct*) ; 

__attribute__((used)) static void gsmld_receive_buf(struct tty_struct *tty, const unsigned char *cp,
			      char *fp, int count)
{
	struct gsm_mux *gsm = tty->disc_data;
	const unsigned char *dp;
	char *f;
	int i;
	char flags = TTY_NORMAL;

	if (debug & 4)
		print_hex_dump_bytes("gsmld_receive: ", DUMP_PREFIX_OFFSET,
				     cp, count);

	for (i = count, dp = cp, f = fp; i; i--, dp++) {
		if (f)
			flags = *f++;
		switch (flags) {
		case TTY_NORMAL:
			gsm->receive(gsm, *dp);
			break;
		case TTY_OVERRUN:
		case TTY_BREAK:
		case TTY_PARITY:
		case TTY_FRAME:
			gsm->error(gsm, *dp, flags);
			break;
		default:
			WARN_ONCE(1, "%s: unknown flag %d\n",
			       tty_name(tty), flags);
			break;
		}
	}
	/* FASYNC if needed ? */
	/* If clogged call tty_throttle(tty); */
}