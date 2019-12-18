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
struct uart_sunzilog_port {int /*<<< orphan*/  port; int /*<<< orphan*/  serio; } ;

/* Variables and functions */
 scalar_t__ ZS_IS_KEYB (struct uart_sunzilog_port*) ; 
 scalar_t__ ZS_IS_MOUSE (struct uart_sunzilog_port*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunzilog_reg ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zs_remove_one(struct uart_sunzilog_port *up)
{
	if (ZS_IS_KEYB(up) || ZS_IS_MOUSE(up)) {
#ifdef CONFIG_SERIO
		serio_unregister_port(&up->serio);
#endif
	} else
		uart_remove_one_port(&sunzilog_reg, &up->port);
}