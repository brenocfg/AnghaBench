#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nr; } ;
struct sccnxp_port {int /*<<< orphan*/  regulator; TYPE_1__ uart; int /*<<< orphan*/ * port; int /*<<< orphan*/  timer; int /*<<< orphan*/  irq; int /*<<< orphan*/  poll; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sccnxp_port*) ; 
 struct sccnxp_port* platform_get_drvdata (struct platform_device*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_remove_one_port (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_unregister_driver (TYPE_1__*) ; 

__attribute__((used)) static int sccnxp_remove(struct platform_device *pdev)
{
	int i;
	struct sccnxp_port *s = platform_get_drvdata(pdev);

	if (!s->poll)
		devm_free_irq(&pdev->dev, s->irq, s);
	else
		del_timer_sync(&s->timer);

	for (i = 0; i < s->uart.nr; i++)
		uart_remove_one_port(&s->uart, &s->port[i]);

	uart_unregister_driver(&s->uart);

	if (!IS_ERR(s->regulator))
		return regulator_disable(s->regulator);

	return 0;
}