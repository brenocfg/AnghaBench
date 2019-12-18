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
typedef  int u16 ;
struct mii_bus {struct hisi_femac_mdio_data* priv; } ;
struct hisi_femac_mdio_data {scalar_t__ membase; } ;

/* Variables and functions */
 int BIT_PHY_ADDR_OFFSET ; 
 int BIT_WR_DATA_OFFSET ; 
 scalar_t__ MDIO_RWCTRL ; 
 int MDIO_WRITE ; 
 int hisi_femac_mdio_wait_ready (struct hisi_femac_mdio_data*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hisi_femac_mdio_write(struct mii_bus *bus, int mii_id, int regnum,
				 u16 value)
{
	struct hisi_femac_mdio_data *data = bus->priv;
	int ret;

	ret = hisi_femac_mdio_wait_ready(data);
	if (ret)
		return ret;

	writel(MDIO_WRITE | (value << BIT_WR_DATA_OFFSET) |
	       (mii_id << BIT_PHY_ADDR_OFFSET) | regnum,
	       data->membase + MDIO_RWCTRL);

	return hisi_femac_mdio_wait_ready(data);
}