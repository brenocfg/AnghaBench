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
typedef  int /*<<< orphan*/  u16 ;
struct mdio_device {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; } ;
struct bcm_ns_usb3 {struct mdio_device* mdiodev; } ;

/* Variables and functions */
 int mdiobus_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_ns_usb3_mdiodev_phy_write(struct bcm_ns_usb3 *usb3, u16 reg,
					 u16 value)
{
	struct mdio_device *mdiodev = usb3->mdiodev;

	return mdiobus_write(mdiodev->bus, mdiodev->addr, reg, value);
}