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
struct wilc {scalar_t__ suspend_event; int /*<<< orphan*/  rtc_clk; } ;
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chip_allow_sleep (struct wilc*) ; 
 int /*<<< orphan*/  chip_wakeup (struct wilc*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  host_sleep_notify (struct wilc*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 struct wilc* sdio_get_drvdata (struct sdio_func*) ; 
 int wilc_sdio_reset (struct wilc*) ; 

__attribute__((used)) static int wilc_sdio_suspend(struct device *dev)
{
	struct sdio_func *func = dev_to_sdio_func(dev);
	struct wilc *wilc = sdio_get_drvdata(func);
	int ret;

	dev_info(dev, "sdio suspend\n");
	chip_wakeup(wilc);

	if (!IS_ERR(wilc->rtc_clk))
		clk_disable_unprepare(wilc->rtc_clk);

	if (wilc->suspend_event) {
		host_sleep_notify(wilc);
		chip_allow_sleep(wilc);
	}

	ret = wilc_sdio_reset(wilc);
	if (ret) {
		dev_err(&func->dev, "Fail reset sdio\n");
		return ret;
	}
	sdio_claim_host(func);

	return 0;
}