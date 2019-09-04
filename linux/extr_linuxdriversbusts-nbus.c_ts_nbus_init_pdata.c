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
struct ts_nbus {void* rdy; void* ale; void* strobe; void* txrx; void* csn; void* data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts_nbus_init_pdata(struct platform_device *pdev, struct ts_nbus
		*ts_nbus)
{
	ts_nbus->data = devm_gpiod_get_array(&pdev->dev, "ts,data",
			GPIOD_OUT_HIGH);
	if (IS_ERR(ts_nbus->data)) {
		dev_err(&pdev->dev, "failed to retrieve ts,data-gpio from dts\n");
		return PTR_ERR(ts_nbus->data);
	}

	ts_nbus->csn = devm_gpiod_get(&pdev->dev, "ts,csn", GPIOD_OUT_HIGH);
	if (IS_ERR(ts_nbus->csn)) {
		dev_err(&pdev->dev, "failed to retrieve ts,csn-gpio from dts\n");
		return PTR_ERR(ts_nbus->csn);
	}

	ts_nbus->txrx = devm_gpiod_get(&pdev->dev, "ts,txrx", GPIOD_OUT_HIGH);
	if (IS_ERR(ts_nbus->txrx)) {
		dev_err(&pdev->dev, "failed to retrieve ts,txrx-gpio from dts\n");
		return PTR_ERR(ts_nbus->txrx);
	}

	ts_nbus->strobe = devm_gpiod_get(&pdev->dev, "ts,strobe", GPIOD_OUT_HIGH);
	if (IS_ERR(ts_nbus->strobe)) {
		dev_err(&pdev->dev, "failed to retrieve ts,strobe-gpio from dts\n");
		return PTR_ERR(ts_nbus->strobe);
	}

	ts_nbus->ale = devm_gpiod_get(&pdev->dev, "ts,ale", GPIOD_OUT_HIGH);
	if (IS_ERR(ts_nbus->ale)) {
		dev_err(&pdev->dev, "failed to retrieve ts,ale-gpio from dts\n");
		return PTR_ERR(ts_nbus->ale);
	}

	ts_nbus->rdy = devm_gpiod_get(&pdev->dev, "ts,rdy", GPIOD_IN);
	if (IS_ERR(ts_nbus->rdy)) {
		dev_err(&pdev->dev, "failed to retrieve ts,rdy-gpio from dts\n");
		return PTR_ERR(ts_nbus->rdy);
	}

	return 0;
}