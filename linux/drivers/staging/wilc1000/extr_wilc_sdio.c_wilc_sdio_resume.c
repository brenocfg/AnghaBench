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
struct wilc {scalar_t__ suspend_event; } ;
struct sdio_func {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chip_allow_sleep (struct wilc*) ; 
 int /*<<< orphan*/  chip_wakeup (struct wilc*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  host_wakeup_notify (struct wilc*) ; 
 struct wilc* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  wilc_sdio_init (struct wilc*,int) ; 

__attribute__((used)) static int wilc_sdio_resume(struct device *dev)
{
	struct sdio_func *func = dev_to_sdio_func(dev);
	struct wilc *wilc = sdio_get_drvdata(func);

	dev_info(dev, "sdio resume\n");
	sdio_release_host(func);
	chip_wakeup(wilc);
	wilc_sdio_init(wilc, true);

	if (wilc->suspend_event)
		host_wakeup_notify(wilc);

	chip_allow_sleep(wilc);

	return 0;
}