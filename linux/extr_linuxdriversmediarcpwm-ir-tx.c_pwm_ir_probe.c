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
struct rc_dev {int /*<<< orphan*/  s_tx_carrier; int /*<<< orphan*/  s_tx_duty_cycle; int /*<<< orphan*/  tx_ir; int /*<<< orphan*/  device_name; int /*<<< orphan*/  driver_name; struct pwm_ir* priv; } ;
struct pwm_ir {int carrier; int duty_cycle; int /*<<< orphan*/  pwm; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW_TX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pwm_ir* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pwm_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rc_dev* devm_rc_allocate_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_rc_register_device (int /*<<< orphan*/ *,struct rc_dev*) ; 
 int /*<<< orphan*/  pwm_ir_set_carrier ; 
 int /*<<< orphan*/  pwm_ir_set_duty_cycle ; 
 int /*<<< orphan*/  pwm_ir_tx ; 

__attribute__((used)) static int pwm_ir_probe(struct platform_device *pdev)
{
	struct pwm_ir *pwm_ir;
	struct rc_dev *rcdev;
	int rc;

	pwm_ir = devm_kmalloc(&pdev->dev, sizeof(*pwm_ir), GFP_KERNEL);
	if (!pwm_ir)
		return -ENOMEM;

	pwm_ir->pwm = devm_pwm_get(&pdev->dev, NULL);
	if (IS_ERR(pwm_ir->pwm))
		return PTR_ERR(pwm_ir->pwm);

	pwm_ir->carrier = 38000;
	pwm_ir->duty_cycle = 50;

	rcdev = devm_rc_allocate_device(&pdev->dev, RC_DRIVER_IR_RAW_TX);
	if (!rcdev)
		return -ENOMEM;

	rcdev->priv = pwm_ir;
	rcdev->driver_name = DRIVER_NAME;
	rcdev->device_name = DEVICE_NAME;
	rcdev->tx_ir = pwm_ir_tx;
	rcdev->s_tx_duty_cycle = pwm_ir_set_duty_cycle;
	rcdev->s_tx_carrier = pwm_ir_set_carrier;

	rc = devm_rc_register_device(&pdev->dev, rcdev);
	if (rc < 0)
		dev_err(&pdev->dev, "failed to register rc device\n");

	return rc;
}