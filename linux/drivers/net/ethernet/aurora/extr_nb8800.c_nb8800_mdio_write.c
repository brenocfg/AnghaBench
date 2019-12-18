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
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int MDIO_CMD_ADDR (int) ; 
 int MDIO_CMD_DATA (int /*<<< orphan*/ ) ; 
 int MDIO_CMD_REG (int) ; 
 int MDIO_CMD_WR ; 
 int nb8800_mdio_cmd (struct mii_bus*,int) ; 

__attribute__((used)) static int nb8800_mdio_write(struct mii_bus *bus, int phy_id, int reg, u16 val)
{
	u32 cmd = MDIO_CMD_ADDR(phy_id) | MDIO_CMD_REG(reg) |
		MDIO_CMD_DATA(val) | MDIO_CMD_WR;

	return nb8800_mdio_cmd(bus, cmd);
}