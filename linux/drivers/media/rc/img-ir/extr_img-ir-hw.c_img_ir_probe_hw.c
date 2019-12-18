#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rc_dev {char* device_name; int /*<<< orphan*/  change_protocol; int /*<<< orphan*/  s_wakeup_filter; int /*<<< orphan*/  s_filter; int /*<<< orphan*/  allowed_protocols; int /*<<< orphan*/  map_name; struct img_ir_priv* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  notifier_call; } ;
struct img_ir_priv_hw {int clk_hz; TYPE_1__ clk_nb; struct rc_dev* rdev; int /*<<< orphan*/  suspend_timer; int /*<<< orphan*/  end_timer; } ;
struct img_ir_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; struct img_ir_priv_hw hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC_DRIVER_SCANCODE ; 
 int /*<<< orphan*/  RC_MAP_EMPTY ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_notifier_register (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  img_ir_allowed_protos (struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_change_protocol ; 
 int /*<<< orphan*/  img_ir_clk_notify ; 
 int /*<<< orphan*/  img_ir_end_timer ; 
 int /*<<< orphan*/  img_ir_init_decoders () ; 
 int /*<<< orphan*/  img_ir_probe_hw_caps (struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_set_decoder (struct img_ir_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_set_normal_filter ; 
 int /*<<< orphan*/  img_ir_set_wakeup_filter ; 
 int /*<<< orphan*/  img_ir_suspend_timer ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int img_ir_probe_hw(struct img_ir_priv *priv)
{
	struct img_ir_priv_hw *hw = &priv->hw;
	struct rc_dev *rdev;
	int error;

	/* Ensure hardware decoders have been preprocessed */
	img_ir_init_decoders();

	/* Probe hardware capabilities */
	img_ir_probe_hw_caps(priv);

	/* Set up the end timer */
	timer_setup(&hw->end_timer, img_ir_end_timer, 0);
	timer_setup(&hw->suspend_timer, img_ir_suspend_timer, 0);

	/* Register a clock notifier */
	if (!IS_ERR(priv->clk)) {
		hw->clk_hz = clk_get_rate(priv->clk);
#ifdef CONFIG_COMMON_CLK
		hw->clk_nb.notifier_call = img_ir_clk_notify;
		error = clk_notifier_register(priv->clk, &hw->clk_nb);
		if (error)
			dev_warn(priv->dev,
				 "failed to register clock notifier\n");
#endif
	} else {
		hw->clk_hz = 32768;
	}

	/* Allocate hardware decoder */
	hw->rdev = rdev = rc_allocate_device(RC_DRIVER_SCANCODE);
	if (!rdev) {
		dev_err(priv->dev, "cannot allocate input device\n");
		error = -ENOMEM;
		goto err_alloc_rc;
	}
	rdev->priv = priv;
	rdev->map_name = RC_MAP_EMPTY;
	rdev->allowed_protocols = img_ir_allowed_protos(priv);
	rdev->device_name = "IMG Infrared Decoder";
	rdev->s_filter = img_ir_set_normal_filter;
	rdev->s_wakeup_filter = img_ir_set_wakeup_filter;

	/* Register hardware decoder */
	error = rc_register_device(rdev);
	if (error) {
		dev_err(priv->dev, "failed to register IR input device\n");
		goto err_register_rc;
	}

	/*
	 * Set this after rc_register_device as no protocols have been
	 * registered yet.
	 */
	rdev->change_protocol = img_ir_change_protocol;

	device_init_wakeup(priv->dev, 1);

	return 0;

err_register_rc:
	img_ir_set_decoder(priv, NULL, 0);
	hw->rdev = NULL;
	rc_free_device(rdev);
err_alloc_rc:
#ifdef CONFIG_COMMON_CLK
	if (!IS_ERR(priv->clk))
		clk_notifier_unregister(priv->clk, &hw->clk_nb);
#endif
	return error;
}