#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct i2c_bus_recovery_info* bus_recovery_info; } ;
struct i2c_bus_recovery_info {int /*<<< orphan*/  recover_bus; int /*<<< orphan*/  unprepare_recovery; int /*<<< orphan*/  prepare_recovery; void* sda_gpiod; void* scl_gpiod; } ;
struct imx_i2c_struct {TYPE_1__ adapter; void* pinctrl_pins_gpio; void* pinctrl_pins_default; void* pinctrl; struct i2c_bus_recovery_info rinfo; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH_OPEN_DRAIN ; 
 scalar_t__ IS_ERR (void*) ; 
 char* PINCTRL_STATE_DEFAULT ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* devm_pinctrl_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_generic_scl_recovery ; 
 int /*<<< orphan*/  i2c_imx_prepare_recovery ; 
 int /*<<< orphan*/  i2c_imx_unprepare_recovery ; 
 void* pinctrl_lookup_state (void*,char*) ; 

__attribute__((used)) static int i2c_imx_init_recovery_info(struct imx_i2c_struct *i2c_imx,
		struct platform_device *pdev)
{
	struct i2c_bus_recovery_info *rinfo = &i2c_imx->rinfo;

	i2c_imx->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (!i2c_imx->pinctrl || IS_ERR(i2c_imx->pinctrl)) {
		dev_info(&pdev->dev, "can't get pinctrl, bus recovery not supported\n");
		return PTR_ERR(i2c_imx->pinctrl);
	}

	i2c_imx->pinctrl_pins_default = pinctrl_lookup_state(i2c_imx->pinctrl,
			PINCTRL_STATE_DEFAULT);
	i2c_imx->pinctrl_pins_gpio = pinctrl_lookup_state(i2c_imx->pinctrl,
			"gpio");
	rinfo->sda_gpiod = devm_gpiod_get(&pdev->dev, "sda", GPIOD_IN);
	rinfo->scl_gpiod = devm_gpiod_get(&pdev->dev, "scl", GPIOD_OUT_HIGH_OPEN_DRAIN);

	if (PTR_ERR(rinfo->sda_gpiod) == -EPROBE_DEFER ||
	    PTR_ERR(rinfo->scl_gpiod) == -EPROBE_DEFER) {
		return -EPROBE_DEFER;
	} else if (IS_ERR(rinfo->sda_gpiod) ||
		   IS_ERR(rinfo->scl_gpiod) ||
		   IS_ERR(i2c_imx->pinctrl_pins_default) ||
		   IS_ERR(i2c_imx->pinctrl_pins_gpio)) {
		dev_dbg(&pdev->dev, "recovery information incomplete\n");
		return 0;
	}

	dev_dbg(&pdev->dev, "using scl%s for recovery\n",
		rinfo->sda_gpiod ? ",sda" : "");

	rinfo->prepare_recovery = i2c_imx_prepare_recovery;
	rinfo->unprepare_recovery = i2c_imx_unprepare_recovery;
	rinfo->recover_bus = i2c_generic_scl_recovery;
	i2c_imx->adapter.bus_recovery_info = rinfo;

	return 0;
}