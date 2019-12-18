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
struct max310x_one {int /*<<< orphan*/  md_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct max310x_one* to_max310x_port (struct uart_port*) ; 

__attribute__((used)) static void max310x_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct max310x_one *one = to_max310x_port(port);

	schedule_work(&one->md_work);
}