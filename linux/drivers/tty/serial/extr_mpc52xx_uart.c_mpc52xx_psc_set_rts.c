#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  op0; int /*<<< orphan*/  op1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPC52xx_PSC_OP_RTS ; 
 TYPE_1__* PSC (struct uart_port*) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc52xx_psc_set_rts(struct uart_port *port, int state)
{
	if (state)
		out_8(&PSC(port)->op1, MPC52xx_PSC_OP_RTS);
	else
		out_8(&PSC(port)->op0, MPC52xx_PSC_OP_RTS);
}