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
struct TYPE_2__ {scalar_t__ type; scalar_t__ membase; } ;
struct uart_sunsu_port {scalar_t__ su_type; int /*<<< orphan*/  reg_size; TYPE_1__ port; int /*<<< orphan*/  serio; } ;
struct platform_device {int /*<<< orphan*/ * resource; } ;

/* Variables and functions */
 scalar_t__ PORT_UNKNOWN ; 
 scalar_t__ SU_PORT_KBD ; 
 scalar_t__ SU_PORT_MS ; 
 int /*<<< orphan*/  kfree (struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 struct uart_sunsu_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunsu_reg ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int su_remove(struct platform_device *op)
{
	struct uart_sunsu_port *up = platform_get_drvdata(op);
	bool kbdms = false;

	if (up->su_type == SU_PORT_MS ||
	    up->su_type == SU_PORT_KBD)
		kbdms = true;

	if (kbdms) {
#ifdef CONFIG_SERIO
		serio_unregister_port(&up->serio);
#endif
	} else if (up->port.type != PORT_UNKNOWN)
		uart_remove_one_port(&sunsu_reg, &up->port);

	if (up->port.membase)
		of_iounmap(&op->resource[0], up->port.membase, up->reg_size);

	if (kbdms)
		kfree(up);

	return 0;
}