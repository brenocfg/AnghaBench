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
struct uniphier8250_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  line; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct uniphier8250_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serial8250_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_uart_remove(struct platform_device *pdev)
{
	struct uniphier8250_priv *priv = platform_get_drvdata(pdev);

	serial8250_unregister_port(priv->line);
	clk_disable_unprepare(priv->clk);

	return 0;
}