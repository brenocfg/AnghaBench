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
struct uart_port {int dummy; } ;
struct msm_port {int /*<<< orphan*/  pclk; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 struct msm_port* UART_TO_MSM (struct uart_port*) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_serial_set_mnd_regs (struct uart_port*) ; 

__attribute__((used)) static void msm_init_clock(struct uart_port *port)
{
	struct msm_port *msm_port = UART_TO_MSM(port);

	clk_prepare_enable(msm_port->clk);
	clk_prepare_enable(msm_port->pclk);
	msm_serial_set_mnd_regs(port);
}