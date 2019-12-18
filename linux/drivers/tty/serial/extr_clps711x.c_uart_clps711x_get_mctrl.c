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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct clps711x_port {int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 struct clps711x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 unsigned int mctrl_gpio_get (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int uart_clps711x_get_mctrl(struct uart_port *port)
{
	unsigned int result = TIOCM_DSR | TIOCM_CTS | TIOCM_CAR;
	struct clps711x_port *s = dev_get_drvdata(port->dev);

	return mctrl_gpio_get(s->gpios, &result);
}