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
struct wilc {int /*<<< orphan*/  rtc_clk; scalar_t__ gpio_irq; } ;
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 struct wilc* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  wilc_netdev_cleanup (struct wilc*) ; 

__attribute__((used)) static void wilc_sdio_remove(struct sdio_func *func)
{
	struct wilc *wilc = sdio_get_drvdata(func);

	/* free the GPIO in module remove */
	if (wilc->gpio_irq)
		gpiod_put(wilc->gpio_irq);

	if (!IS_ERR(wilc->rtc_clk))
		clk_disable_unprepare(wilc->rtc_clk);

	wilc_netdev_cleanup(wilc);
}