#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_8__ {TYPE_2__* adapter; TYPE_1__* dram; } ;
struct TYPE_7__ {int /*<<< orphan*/  kref; } ;
struct TYPE_6__ {int /*<<< orphan*/  CmdReg; } ;

/* Variables and functions */
 unsigned char CMD_RCV_ENABLE ; 
 TYPE_3__* ICOM_PORT ; 
 int /*<<< orphan*/  icom_kref_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown (TYPE_3__*) ; 
 int /*<<< orphan*/  trace (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icom_close(struct uart_port *port)
{
	unsigned char cmdReg;

	trace(ICOM_PORT, "CLOSE", 0);

	/* stop receiver */
	cmdReg = readb(&ICOM_PORT->dram->CmdReg);
	writeb(cmdReg & ~CMD_RCV_ENABLE, &ICOM_PORT->dram->CmdReg);

	shutdown(ICOM_PORT);

	kref_put(&ICOM_PORT->adapter->kref, icom_kref_release);
}