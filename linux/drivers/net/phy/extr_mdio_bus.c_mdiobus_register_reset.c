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
struct reset_control {int dummy; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct mdio_device {struct reset_control* reset_ctrl; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTSUPP ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 struct reset_control* devm_reset_control_get_exclusive (TYPE_1__*,char*) ; 

__attribute__((used)) static int mdiobus_register_reset(struct mdio_device *mdiodev)
{
	struct reset_control *reset = NULL;

	if (mdiodev->dev.of_node)
		reset = devm_reset_control_get_exclusive(&mdiodev->dev,
							 "phy");
	if (PTR_ERR(reset) == -ENOENT ||
	    PTR_ERR(reset) == -ENOTSUPP)
		reset = NULL;
	else if (IS_ERR(reset))
		return PTR_ERR(reset);

	mdiodev->reset_ctrl = reset;

	return 0;
}