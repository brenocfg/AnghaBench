#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dram; } ;
struct TYPE_4__ {int /*<<< orphan*/  CmdReg; } ;

/* Variables and functions */
 unsigned char CMD_HOLD_XMIT ; 
 TYPE_2__* ICOM_PORT ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icom_stop_tx(struct uart_port *port)
{
	unsigned char cmdReg;

	trace(ICOM_PORT, "STOP", 0);
	cmdReg = readb(&ICOM_PORT->dram->CmdReg);
	writeb(cmdReg | CMD_HOLD_XMIT, &ICOM_PORT->dram->CmdReg);
}