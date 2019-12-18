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
struct rc_dev {char* device_name; int /*<<< orphan*/  map_name; struct img_ir_priv* priv; } ;
struct img_ir_priv_raw {struct rc_dev* rdev; int /*<<< orphan*/  timer; } ;
struct img_ir_priv {int /*<<< orphan*/  dev; struct img_ir_priv_raw raw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  RC_MAP_EMPTY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  img_ir_echo_timer ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int img_ir_probe_raw(struct img_ir_priv *priv)
{
	struct img_ir_priv_raw *raw = &priv->raw;
	struct rc_dev *rdev;
	int error;

	/* Set up the echo timer */
	timer_setup(&raw->timer, img_ir_echo_timer, 0);

	/* Allocate raw decoder */
	raw->rdev = rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	if (!rdev) {
		dev_err(priv->dev, "cannot allocate raw input device\n");
		return -ENOMEM;
	}
	rdev->priv = priv;
	rdev->map_name = RC_MAP_EMPTY;
	rdev->device_name = "IMG Infrared Decoder Raw";

	/* Register raw decoder */
	error = rc_register_device(rdev);
	if (error) {
		dev_err(priv->dev, "failed to register raw IR input device\n");
		rc_free_device(rdev);
		raw->rdev = NULL;
		return error;
	}

	return 0;
}