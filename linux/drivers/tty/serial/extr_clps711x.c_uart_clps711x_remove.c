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
struct platform_device {int dummy; } ;
struct clps711x_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  clps711x_uart ; 
 struct clps711x_port* platform_get_drvdata (struct platform_device*) ; 
 int uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uart_clps711x_remove(struct platform_device *pdev)
{
	struct clps711x_port *s = platform_get_drvdata(pdev);

	return uart_remove_one_port(&clps711x_uart, &s->port);
}