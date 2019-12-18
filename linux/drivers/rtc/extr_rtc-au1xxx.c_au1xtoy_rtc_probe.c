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
struct rtc_device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU1000_SYS_CNTRCTRL ; 
 int /*<<< orphan*/  AU1000_SYS_TOYTRIM ; 
 unsigned long CNTR_OK ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int SYS_CNTRL_C0S ; 
 int SYS_CNTRL_T0S ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1xtoy_rtc_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct rtc_device* devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtc_device*) ; 

__attribute__((used)) static int au1xtoy_rtc_probe(struct platform_device *pdev)
{
	struct rtc_device *rtcdev;
	unsigned long t;
	int ret;

	t = alchemy_rdsys(AU1000_SYS_CNTRCTRL);
	if (!(t & CNTR_OK)) {
		dev_err(&pdev->dev, "counters not working; aborting.\n");
		ret = -ENODEV;
		goto out_err;
	}

	ret = -ETIMEDOUT;

	/* set counter0 tickrate to 1Hz if necessary */
	if (alchemy_rdsys(AU1000_SYS_TOYTRIM) != 32767) {
		/* wait until hardware gives access to TRIM register */
		t = 0x00100000;
		while ((alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_T0S) && --t)
			msleep(1);

		if (!t) {
			/* timed out waiting for register access; assume
			 * counters are unusable.
			 */
			dev_err(&pdev->dev, "timeout waiting for access\n");
			goto out_err;
		}

		/* set 1Hz TOY tick rate */
		alchemy_wrsys(32767, AU1000_SYS_TOYTRIM);
	}

	/* wait until the hardware allows writes to the counter reg */
	while (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_C0S)
		msleep(1);

	rtcdev = devm_rtc_device_register(&pdev->dev, "rtc-au1xxx",
				     &au1xtoy_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtcdev)) {
		ret = PTR_ERR(rtcdev);
		goto out_err;
	}

	platform_set_drvdata(pdev, rtcdev);

	return 0;

out_err:
	return ret;
}