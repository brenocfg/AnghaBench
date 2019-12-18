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
typedef  scalar_t__ u32 ;
struct mii_bus {struct hns_mdio_device* priv; } ;
struct hns_mdio_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MDIO_CMD_START_B ; 
 int /*<<< orphan*/  MDIO_COMMAND_REG ; 
 scalar_t__ MDIO_GET_REG_BIT (struct hns_mdio_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MDIO_TIMEOUT ; 

__attribute__((used)) static int hns_mdio_wait_ready(struct mii_bus *bus)
{
	struct hns_mdio_device *mdio_dev = bus->priv;
	u32 cmd_reg_value;
	int i;

	/* waitting for MDIO_COMMAND_REG 's mdio_start==0 */
	/* after that can do read or write*/
	for (i = 0; i < MDIO_TIMEOUT; i++) {
		cmd_reg_value = MDIO_GET_REG_BIT(mdio_dev,
						 MDIO_COMMAND_REG,
						 MDIO_CMD_START_B);
		if (!cmd_reg_value)
			break;
	}
	if ((i == MDIO_TIMEOUT) && cmd_reg_value)
		return -ETIMEDOUT;

	return 0;
}