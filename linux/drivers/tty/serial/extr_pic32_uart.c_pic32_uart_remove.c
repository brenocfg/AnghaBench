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
struct platform_device {int dummy; } ;
struct pic32_sport {size_t idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  pic32_disable_clock (struct pic32_sport*) ; 
 int /*<<< orphan*/ ** pic32_sports ; 
 int /*<<< orphan*/  pic32_uart_driver ; 
 struct uart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 struct pic32_sport* to_pic32_sport (struct uart_port*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int pic32_uart_remove(struct platform_device *pdev)
{
	struct uart_port *port = platform_get_drvdata(pdev);
	struct pic32_sport *sport = to_pic32_sport(port);

	uart_remove_one_port(&pic32_uart_driver, port);
	pic32_disable_clock(sport);
	platform_set_drvdata(pdev, NULL);
	pic32_sports[sport->idx] = NULL;

	/* automatic unroll of sport and gpios */
	return 0;
}