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
typedef  int /*<<< orphan*/  u16 ;
struct lan9303_mdio {TYPE_1__* device; } ;
struct lan9303 {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 struct lan9303_mdio* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int mdiobus_write_nested (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_mdio_phy_write(struct lan9303 *chip, int phy, int reg,
				  u16 val)
{
	struct lan9303_mdio *sw_dev = dev_get_drvdata(chip->dev);

	return mdiobus_write_nested(sw_dev->device->bus, phy, reg, val);
}