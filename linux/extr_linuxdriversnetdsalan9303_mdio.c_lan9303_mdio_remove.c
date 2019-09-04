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
struct mdio_device {int /*<<< orphan*/  dev; } ;
struct lan9303_mdio {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 struct lan9303_mdio* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lan9303_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan9303_mdio_remove(struct mdio_device *mdiodev)
{
	struct lan9303_mdio *sw_dev = dev_get_drvdata(&mdiodev->dev);

	if (!sw_dev)
		return;

	lan9303_remove(&sw_dev->chip);
}