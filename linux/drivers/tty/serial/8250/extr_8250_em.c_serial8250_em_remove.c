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
struct serial8250_em_priv {int /*<<< orphan*/  sclk; int /*<<< orphan*/  line; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct serial8250_em_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serial8250_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serial8250_em_remove(struct platform_device *pdev)
{
	struct serial8250_em_priv *priv = platform_get_drvdata(pdev);

	serial8250_unregister_port(priv->line);
	clk_disable_unprepare(priv->sclk);
	return 0;
}