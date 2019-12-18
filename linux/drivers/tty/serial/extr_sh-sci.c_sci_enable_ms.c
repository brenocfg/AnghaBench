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
struct TYPE_2__ {int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  mctrl_gpio_enable_ms (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static void sci_enable_ms(struct uart_port *port)
{
	mctrl_gpio_enable_ms(to_sci_port(port)->gpios);
}