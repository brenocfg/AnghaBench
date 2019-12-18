#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rc_dev {int /*<<< orphan*/  driver_name; int /*<<< orphan*/  s_tx_carrier; int /*<<< orphan*/  s_tx_duty_cycle; int /*<<< orphan*/  tx_ir; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__* priv; } ;
struct pwm_device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct TYPE_3__ {struct rc_dev* rcdev; int /*<<< orphan*/ * dev; TYPE_2__ timer; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 scalar_t__ IS_ERR (struct pwm_device*) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int PTR_ERR (struct pwm_device*) ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW_TX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rc_dev* devm_rc_allocate_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_rc_register_device (int /*<<< orphan*/ *,struct rc_dev*) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ ir_rx51 ; 
 int /*<<< orphan*/  ir_rx51_open ; 
 int /*<<< orphan*/  ir_rx51_release ; 
 int /*<<< orphan*/  ir_rx51_set_duty_cycle ; 
 int /*<<< orphan*/  ir_rx51_set_tx_carrier ; 
 int /*<<< orphan*/  ir_rx51_timer_cb ; 
 int /*<<< orphan*/  ir_rx51_tx ; 
 struct pwm_device* pwm_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_get_period (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_put (struct pwm_device*) ; 

__attribute__((used)) static int ir_rx51_probe(struct platform_device *dev)
{
	struct pwm_device *pwm;
	struct rc_dev *rcdev;

	pwm = pwm_get(&dev->dev, NULL);
	if (IS_ERR(pwm)) {
		int err = PTR_ERR(pwm);

		if (err != -EPROBE_DEFER)
			dev_err(&dev->dev, "pwm_get failed: %d\n", err);
		return err;
	}

	/* Use default, in case userspace does not set the carrier */
	ir_rx51.freq = DIV_ROUND_CLOSEST(pwm_get_period(pwm), NSEC_PER_SEC);
	pwm_put(pwm);

	hrtimer_init(&ir_rx51.timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	ir_rx51.timer.function = ir_rx51_timer_cb;

	ir_rx51.dev = &dev->dev;

	rcdev = devm_rc_allocate_device(&dev->dev, RC_DRIVER_IR_RAW_TX);
	if (!rcdev)
		return -ENOMEM;

	rcdev->priv = &ir_rx51;
	rcdev->open = ir_rx51_open;
	rcdev->close = ir_rx51_release;
	rcdev->tx_ir = ir_rx51_tx;
	rcdev->s_tx_duty_cycle = ir_rx51_set_duty_cycle;
	rcdev->s_tx_carrier = ir_rx51_set_tx_carrier;
	rcdev->driver_name = KBUILD_MODNAME;

	ir_rx51.rcdev = rcdev;

	return devm_rc_register_device(&dev->dev, ir_rx51.rcdev);
}