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
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static void msm_power(struct uart_port *port, unsigned int state,
		      unsigned int oldstate)
{
	struct msm_port *msm_port = UART_TO_MSM(port);

	switch (state) {
	case 0:
		clk_prepare_enable(msm_port->clk);
		clk_prepare_enable(msm_port->pclk);
		break;
	case 3:
		clk_disable_unprepare(msm_port->clk);
		clk_disable_unprepare(msm_port->pclk);
		break;
	default:
		pr_err("msm_serial: Unknown PM state %d\n", state);
	}
}