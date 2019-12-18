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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* default_trigger; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  brightness; int /*<<< orphan*/  name; } ;
struct rtsx_usb_sdmmc {int /*<<< orphan*/  led_work; TYPE_3__ led; int /*<<< orphan*/  led_name; int /*<<< orphan*/  host_mutex; struct platform_device* pdev; struct mmc_host* mmc; struct rtsx_ucr* ucr; } ;
struct rtsx_ucr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int led_classdev_register (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 char* mmc_hostname (struct mmc_host*) ; 
 struct rtsx_usb_sdmmc* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtsx_usb_sdmmc*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  rtsx_usb_init_host (struct rtsx_usb_sdmmc*) ; 
 int /*<<< orphan*/  rtsx_usb_led_control ; 
 int /*<<< orphan*/  rtsx_usb_update_led ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  to_usb_interface (int /*<<< orphan*/ ) ; 
 struct rtsx_ucr* usb_get_intfdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtsx_usb_sdmmc_drv_probe(struct platform_device *pdev)
{
	struct mmc_host *mmc;
	struct rtsx_usb_sdmmc *host;
	struct rtsx_ucr *ucr;
#ifdef RTSX_USB_USE_LEDS_CLASS
	int err;
#endif

	ucr = usb_get_intfdata(to_usb_interface(pdev->dev.parent));
	if (!ucr)
		return -ENXIO;

	dev_dbg(&(pdev->dev), ": Realtek USB SD/MMC controller found\n");

	mmc = mmc_alloc_host(sizeof(*host), &pdev->dev);
	if (!mmc)
		return -ENOMEM;

	host = mmc_priv(mmc);
	host->ucr = ucr;
	host->mmc = mmc;
	host->pdev = pdev;
	platform_set_drvdata(pdev, host);

	mutex_init(&host->host_mutex);
	rtsx_usb_init_host(host);
	pm_runtime_enable(&pdev->dev);

#ifdef RTSX_USB_USE_LEDS_CLASS
	snprintf(host->led_name, sizeof(host->led_name),
		"%s::", mmc_hostname(mmc));
	host->led.name = host->led_name;
	host->led.brightness = LED_OFF;
	host->led.default_trigger = mmc_hostname(mmc);
	host->led.brightness_set = rtsx_usb_led_control;

	err = led_classdev_register(mmc_dev(mmc), &host->led);
	if (err)
		dev_err(&(pdev->dev),
				"Failed to register LED device: %d\n", err);
	INIT_WORK(&host->led_work, rtsx_usb_update_led);

#endif
	mmc_add_host(mmc);

	return 0;
}