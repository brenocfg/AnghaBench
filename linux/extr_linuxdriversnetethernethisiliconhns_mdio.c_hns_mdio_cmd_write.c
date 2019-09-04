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
typedef  int u32 ;
typedef  int u16 ;
struct hns_mdio_device {int dummy; } ;

/* Variables and functions */
 int MDIO_CMD_DEVAD_M ; 
 int MDIO_CMD_DEVAD_S ; 
 int MDIO_CMD_OP_S ; 
 int MDIO_CMD_PRTAD_M ; 
 int MDIO_CMD_PRTAD_S ; 
 int MDIO_CMD_START_B ; 
 int MDIO_CMD_ST_S ; 
 int /*<<< orphan*/  MDIO_COMMAND_REG ; 
 int MDIO_ST_CLAUSE_22 ; 
 int MDIO_ST_CLAUSE_45 ; 
 int /*<<< orphan*/  MDIO_WRITE_REG (struct hns_mdio_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_mdio_cmd_write(struct hns_mdio_device *mdio_dev,
			       u8 is_c45, u8 op, u8 phy_id, u16 cmd)
{
	u32 cmd_reg_value;
	u8 st = is_c45 ? MDIO_ST_CLAUSE_45 : MDIO_ST_CLAUSE_22;

	cmd_reg_value = st << MDIO_CMD_ST_S;
	cmd_reg_value |= op << MDIO_CMD_OP_S;
	cmd_reg_value |=
		(phy_id & MDIO_CMD_PRTAD_M) << MDIO_CMD_PRTAD_S;
	cmd_reg_value |= (cmd & MDIO_CMD_DEVAD_M) << MDIO_CMD_DEVAD_S;
	cmd_reg_value |= 1 << MDIO_CMD_START_B;

	MDIO_WRITE_REG(mdio_dev, MDIO_COMMAND_REG, cmd_reg_value);
}