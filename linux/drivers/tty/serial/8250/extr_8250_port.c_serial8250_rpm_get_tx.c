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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct uart_8250_port {int capabilities; TYPE_1__ port; int /*<<< orphan*/  rpm_tx_active; } ;

/* Variables and functions */
 int UART_CAP_RPM ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 unsigned char xchg (int /*<<< orphan*/ *,int) ; 

void serial8250_rpm_get_tx(struct uart_8250_port *p)
{
	unsigned char rpm_active;

	if (!(p->capabilities & UART_CAP_RPM))
		return;

	rpm_active = xchg(&p->rpm_tx_active, 1);
	if (rpm_active)
		return;
	pm_runtime_get_sync(p->port.dev);
}