#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thermal_cooling_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  notifier_call; } ;
struct rpi_poe_fan_ctx {TYPE_1__ nb; struct thermal_cooling_device* cdev; int /*<<< orphan*/  pwm_value; int /*<<< orphan*/  fw; int /*<<< orphan*/  def_pwm_value; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
typedef  struct thermal_cooling_device device ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_THERMAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  POE_CUR_PWM ; 
 int /*<<< orphan*/  POE_DEF_PWM ; 
 int PTR_ERR (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct thermal_cooling_device* devm_hwmon_device_register_with_groups (TYPE_2__*,char*,struct rpi_poe_fan_ctx*,int /*<<< orphan*/ ) ; 
 struct rpi_poe_fan_ctx* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rpi_poe_fan_ctx*) ; 
 int read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int register_reboot_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  rpi_firmware_get (struct device_node*) ; 
 int /*<<< orphan*/  rpi_poe_fan_cooling_ops ; 
 int /*<<< orphan*/  rpi_poe_fan_groups ; 
 int rpi_poe_fan_of_get_cooling_data (TYPE_2__*,struct rpi_poe_fan_ctx*) ; 
 int /*<<< orphan*/  rpi_poe_fan_update_state (struct rpi_poe_fan_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpi_poe_reboot ; 
 int /*<<< orphan*/  thermal_cdev_update (struct thermal_cooling_device*) ; 
 struct thermal_cooling_device* thermal_of_cooling_device_register (struct device_node*,char*,struct rpi_poe_fan_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (TYPE_1__*) ; 

__attribute__((used)) static int rpi_poe_fan_probe(struct platform_device *pdev)
{
	struct thermal_cooling_device *cdev;
	struct rpi_poe_fan_ctx *ctx;
	struct device *hwmon;
	struct device_node *np = pdev->dev.of_node;
	struct device_node *fw_node;
	int ret;

	fw_node = of_parse_phandle(np, "firmware", 0);
	if (!fw_node) {
		dev_err(&pdev->dev, "Missing firmware node\n");
		return -ENOENT;
	}

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	mutex_init(&ctx->lock);

	ctx->fw = rpi_firmware_get(fw_node);
	if (!ctx->fw)
		return -EPROBE_DEFER;

	platform_set_drvdata(pdev, ctx);

	ctx->nb.notifier_call = rpi_poe_reboot;
	ret = register_reboot_notifier(&ctx->nb);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register reboot notifier: %i\n",
			ret);
		return ret;
	}
	ret = read_reg(ctx->fw, POE_DEF_PWM, &ctx->def_pwm_value);
	if (ret) {
		dev_err(&pdev->dev, "Failed to get default PWM value: %i\n",
			ret);
		goto err;
	}
	ret = read_reg(ctx->fw, POE_CUR_PWM, &ctx->pwm_value);
	if (ret) {
		dev_err(&pdev->dev, "Failed to get current PWM value: %i\n",
			ret);
		goto err;
	}

	hwmon = devm_hwmon_device_register_with_groups(&pdev->dev, "rpipoefan",
						       ctx, rpi_poe_fan_groups);
	if (IS_ERR(hwmon)) {
		dev_err(&pdev->dev, "Failed to register hwmon device\n");
		ret = PTR_ERR(hwmon);
		goto err;
	}

	ret = rpi_poe_fan_of_get_cooling_data(&pdev->dev, ctx);
	if (ret)
		return ret;

	rpi_poe_fan_update_state(ctx, ctx->pwm_value);
	if (!IS_ENABLED(CONFIG_THERMAL))
		return 0;

	cdev = thermal_of_cooling_device_register(np,
						  "rpi-poe-fan", ctx,
						  &rpi_poe_fan_cooling_ops);
	if (IS_ERR(cdev)) {
		dev_err(&pdev->dev,
			"Failed to register rpi-poe-fan as cooling device");
		ret = PTR_ERR(cdev);
		goto err;
	}
	ctx->cdev = cdev;
	thermal_cdev_update(cdev);

	return 0;
err:
	unregister_reboot_notifier(&ctx->nb);
	return ret;
}