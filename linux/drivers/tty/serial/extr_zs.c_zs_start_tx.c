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
struct zs_scc {int /*<<< orphan*/  zlock; } ;
struct zs_port {scalar_t__ tx_stopped; struct zs_scc* scc; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct zs_port* to_zport (struct uart_port*) ; 
 int /*<<< orphan*/  zs_raw_transmit_chars (struct zs_port*) ; 
 int /*<<< orphan*/  zs_transmit_drain (struct zs_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zs_start_tx(struct uart_port *uport)
{
	struct zs_port *zport = to_zport(uport);
	struct zs_scc *scc = zport->scc;

	spin_lock(&scc->zlock);
	if (zport->tx_stopped) {
		zs_transmit_drain(zport, 0);
		zport->tx_stopped = 0;
		zs_raw_transmit_chars(zport);
	}
	spin_unlock(&scc->zlock);
}