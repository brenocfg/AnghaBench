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
typedef  int u32 ;
struct phy_device {int speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET1011C_CONFIG_REG ; 
 int ET1011C_GIGABIT_SPEED ; 
 int ET1011C_GMII_INTERFACE ; 
 int ET1011C_SPEED_MASK ; 
 int /*<<< orphan*/  ET1011C_STATUS_REG ; 
 int ET1011C_SYS_CLK_EN ; 
 int ET1011C_TX_FIFO_DEPTH_16 ; 
 int ET1011C_TX_FIFO_MASK ; 
 int genphy_read_status (struct phy_device*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int et1011c_read_status(struct phy_device *phydev)
{
	int ret;
	u32 val;
	static int speed;
	ret = genphy_read_status(phydev);

	if (speed != phydev->speed) {
		speed = phydev->speed;
		val = phy_read(phydev, ET1011C_STATUS_REG);
		if ((val & ET1011C_SPEED_MASK) ==
					ET1011C_GIGABIT_SPEED) {
			val = phy_read(phydev, ET1011C_CONFIG_REG);
			val &= ~ET1011C_TX_FIFO_MASK;
			phy_write(phydev, ET1011C_CONFIG_REG, val\
					| ET1011C_GMII_INTERFACE\
					| ET1011C_SYS_CLK_EN\
					| ET1011C_TX_FIFO_DEPTH_16);

		}
	}
	return ret;
}