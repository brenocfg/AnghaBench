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
typedef  unsigned int u64 ;
struct uart_port {int dummy; } ;
struct serial_iso7816 {int /*<<< orphan*/  clk; } ;
struct atmel_uart_port {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned int,int /*<<< orphan*/ ) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static unsigned int atmel_calc_cd(struct uart_port *port,
				  struct serial_iso7816 *iso7816conf)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	unsigned int cd;
	u64 mck_rate;

	mck_rate = (u64)clk_get_rate(atmel_port->clk);
	do_div(mck_rate, iso7816conf->clk);
	cd = mck_rate;
	return cd;
}