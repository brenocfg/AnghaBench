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
typedef  int u8 ;
struct zs_scc {int /*<<< orphan*/  zlock; } ;
struct zs_port {struct zs_scc* scc; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int ALL_SNT ; 
 int /*<<< orphan*/  R1 ; 
 unsigned int TIOCSER_TEMT ; 
 int read_zsreg (struct zs_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct zs_port* to_zport (struct uart_port*) ; 

__attribute__((used)) static unsigned int zs_tx_empty(struct uart_port *uport)
{
	struct zs_port *zport = to_zport(uport);
	struct zs_scc *scc = zport->scc;
	unsigned long flags;
	u8 status;

	spin_lock_irqsave(&scc->zlock, flags);
	status = read_zsreg(zport, R1);
	spin_unlock_irqrestore(&scc->zlock, flags);

	return status & ALL_SNT ? TIOCSER_TEMT : 0;
}