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
struct uart_8250_port {int dummy; } ;
struct omap8250_priv {int habit; int /*<<< orphan*/  mdr1; } ;

/* Variables and functions */
 int UART_ERRATA_i202_MDR1_ACCESS ; 
 int /*<<< orphan*/  UART_OMAP_MDR1 ; 
 int /*<<< orphan*/  omap_8250_mdr1_errataset (struct uart_8250_port*,struct omap8250_priv*) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap8250_update_mdr1(struct uart_8250_port *up,
				 struct omap8250_priv *priv)
{
	if (priv->habit & UART_ERRATA_i202_MDR1_ACCESS)
		omap_8250_mdr1_errataset(up, priv);
	else
		serial_out(up, UART_OMAP_MDR1, priv->mdr1);
}