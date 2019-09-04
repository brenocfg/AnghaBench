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
struct rfkill {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  H1940_LATCH_BLUETOOTH_POWER ; 
 int /*<<< orphan*/  RFKILL_TYPE_BLUETOOTH ; 
 int /*<<< orphan*/  S3C2410_GPH (int) ; 
 int /*<<< orphan*/  S3C2410_GPH0_nCTS0 ; 
 int /*<<< orphan*/  S3C2410_GPH2_TXD0 ; 
 int /*<<< orphan*/  S3C2410_GPH3_RXD0 ; 
 int /*<<< orphan*/  S3C2410_GPIO_OUTPUT ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h1940bt_rfkill_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rfkill*) ; 
 struct rfkill* rfkill_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int rfkill_register (struct rfkill*) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_setpull (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int h1940bt_probe(struct platform_device *pdev)
{
	struct rfkill *rfk;
	int ret = 0;

	ret = gpio_request(S3C2410_GPH(1), dev_name(&pdev->dev));
	if (ret) {
		dev_err(&pdev->dev, "could not get GPH1\n");
		return ret;
	}

	ret = gpio_request(H1940_LATCH_BLUETOOTH_POWER, dev_name(&pdev->dev));
	if (ret) {
		gpio_free(S3C2410_GPH(1));
		dev_err(&pdev->dev, "could not get BT_POWER\n");
		return ret;
	}

	/* Configures BT serial port GPIOs */
	s3c_gpio_cfgpin(S3C2410_GPH(0), S3C2410_GPH0_nCTS0);
	s3c_gpio_setpull(S3C2410_GPH(0), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPH(1), S3C2410_GPIO_OUTPUT);
	s3c_gpio_setpull(S3C2410_GPH(1), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPH(2), S3C2410_GPH2_TXD0);
	s3c_gpio_setpull(S3C2410_GPH(2), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPH(3), S3C2410_GPH3_RXD0);
	s3c_gpio_setpull(S3C2410_GPH(3), S3C_GPIO_PULL_NONE);

	rfk = rfkill_alloc(DRV_NAME, &pdev->dev, RFKILL_TYPE_BLUETOOTH,
			&h1940bt_rfkill_ops, NULL);
	if (!rfk) {
		ret = -ENOMEM;
		goto err_rfk_alloc;
	}

	ret = rfkill_register(rfk);
	if (ret)
		goto err_rfkill;

	platform_set_drvdata(pdev, rfk);

	return 0;

err_rfkill:
	rfkill_destroy(rfk);
err_rfk_alloc:
	return ret;
}