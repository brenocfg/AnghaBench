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
struct zs_scc {int /*<<< orphan*/  zlock; struct zs_port* zport; } ;
struct zs_port {int* regs; struct zs_scc* scc; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int BRKIE ; 
 int CTSIE ; 
 int DCDIE ; 
 int EXT_INT_ENAB ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R15 ; 
 int RxINT_DISAB ; 
 int RxINT_MASK ; 
 int SYNCIE ; 
 int TxINT_ENAB ; 
 size_t ZS_CHAN_A ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct zs_port* to_zport (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct zs_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zs_stop_rx(struct uart_port *uport)
{
	struct zs_port *zport = to_zport(uport);
	struct zs_scc *scc = zport->scc;
	struct zs_port *zport_a = &scc->zport[ZS_CHAN_A];

	spin_lock(&scc->zlock);
	zport->regs[15] &= ~BRKIE;
	zport->regs[1] &= ~(RxINT_MASK | TxINT_ENAB);
	zport->regs[1] |= RxINT_DISAB;

	if (zport != zport_a) {
		/* A-side DCD tracks RI and SYNC tracks DSR.  */
		zport_a->regs[15] &= ~(DCDIE | SYNCIE);
		write_zsreg(zport_a, R15, zport_a->regs[15]);
		if (!(zport_a->regs[15] & BRKIE)) {
			zport_a->regs[1] &= ~EXT_INT_ENAB;
			write_zsreg(zport_a, R1, zport_a->regs[1]);
		}

		/* This-side DCD tracks DCD and CTS tracks CTS.  */
		zport->regs[15] &= ~(DCDIE | CTSIE);
		zport->regs[1] &= ~EXT_INT_ENAB;
	} else {
		/* DCD tracks RI and SYNC tracks DSR for the B side.  */
		if (!(zport->regs[15] & (DCDIE | SYNCIE)))
			zport->regs[1] &= ~EXT_INT_ENAB;
	}

	write_zsreg(zport, R15, zport->regs[15]);
	write_zsreg(zport, R1, zport->regs[1]);
	spin_unlock(&scc->zlock);
}