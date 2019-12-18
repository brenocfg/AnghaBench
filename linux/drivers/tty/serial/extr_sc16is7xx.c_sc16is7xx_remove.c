#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sc16is7xx_port {int /*<<< orphan*/  clk; int /*<<< orphan*/  kworker_task; int /*<<< orphan*/  kworker; TYPE_2__* p; TYPE_1__* devtype; int /*<<< orphan*/  gpio; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  line; } ;
struct TYPE_6__ {TYPE_3__ port; } ;
struct TYPE_5__ {int nr_uart; scalar_t__ nr_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sc16is7xx_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_flush_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc16is7xx_lines ; 
 int /*<<< orphan*/  sc16is7xx_power (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc16is7xx_uart ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int sc16is7xx_remove(struct device *dev)
{
	struct sc16is7xx_port *s = dev_get_drvdata(dev);
	int i;

#ifdef CONFIG_GPIOLIB
	if (s->devtype->nr_gpio)
		gpiochip_remove(&s->gpio);
#endif

	for (i = 0; i < s->devtype->nr_uart; i++) {
		uart_remove_one_port(&sc16is7xx_uart, &s->p[i].port);
		clear_bit(s->p[i].port.line, &sc16is7xx_lines);
		sc16is7xx_power(&s->p[i].port, 0);
	}

	kthread_flush_worker(&s->kworker);
	kthread_stop(s->kworker_task);

	if (!IS_ERR(s->clk))
		clk_disable_unprepare(s->clk);

	return 0;
}