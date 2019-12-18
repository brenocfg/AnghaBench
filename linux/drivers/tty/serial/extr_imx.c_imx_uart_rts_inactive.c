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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  mctrl; } ;
struct imx_port {TYPE_1__ port; int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCM_RTS ; 
 int /*<<< orphan*/  UCR2_CTS ; 
 int /*<<< orphan*/  UCR2_CTSC ; 
 int /*<<< orphan*/  mctrl_gpio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_uart_rts_inactive(struct imx_port *sport, u32 *ucr2)
{
	*ucr2 &= ~UCR2_CTSC;
	*ucr2 |= UCR2_CTS;

	sport->port.mctrl &= ~TIOCM_RTS;
	mctrl_gpio_set(sport->gpios, sport->port.mctrl);
}