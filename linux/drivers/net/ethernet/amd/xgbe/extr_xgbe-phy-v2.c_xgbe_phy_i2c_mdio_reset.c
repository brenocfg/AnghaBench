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
typedef  int u8 ;
struct xgbe_prv_data {struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int mdio_reset_gpio; int /*<<< orphan*/  mdio_reset_addr; } ;
typedef  int /*<<< orphan*/  gpio_reg ;
typedef  int /*<<< orphan*/  gpio_ports ;
typedef  int /*<<< orphan*/  gpio_data ;

/* Variables and functions */
 int xgbe_phy_i2c_read (struct xgbe_prv_data*,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int xgbe_phy_i2c_write (struct xgbe_prv_data*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int xgbe_phy_i2c_mdio_reset(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	u8 gpio_reg, gpio_ports[2], gpio_data[3];
	int ret;

	/* Read the output port registers */
	gpio_reg = 2;
	ret = xgbe_phy_i2c_read(pdata, phy_data->mdio_reset_addr,
				&gpio_reg, sizeof(gpio_reg),
				gpio_ports, sizeof(gpio_ports));
	if (ret)
		return ret;

	/* Prepare to write the GPIO data */
	gpio_data[0] = 2;
	gpio_data[1] = gpio_ports[0];
	gpio_data[2] = gpio_ports[1];

	/* Set the GPIO pin */
	if (phy_data->mdio_reset_gpio < 8)
		gpio_data[1] |= (1 << (phy_data->mdio_reset_gpio % 8));
	else
		gpio_data[2] |= (1 << (phy_data->mdio_reset_gpio % 8));

	/* Write the output port registers */
	ret = xgbe_phy_i2c_write(pdata, phy_data->mdio_reset_addr,
				 gpio_data, sizeof(gpio_data));
	if (ret)
		return ret;

	/* Clear the GPIO pin */
	if (phy_data->mdio_reset_gpio < 8)
		gpio_data[1] &= ~(1 << (phy_data->mdio_reset_gpio % 8));
	else
		gpio_data[2] &= ~(1 << (phy_data->mdio_reset_gpio % 8));

	/* Write the output port registers */
	ret = xgbe_phy_i2c_write(pdata, phy_data->mdio_reset_addr,
				 gpio_data, sizeof(gpio_data));

	return ret;
}