#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int id_rev; } ;
struct lan743x_adapter {TYPE_3__* mdiobus; TYPE_1__ csr; TYPE_2__* pdev; } ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  phy_mask; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; void* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int ENOMEM ; 
 int ID_REV_ID_LAN7430_ ; 
 int ID_REV_ID_MASK_ ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 TYPE_3__* devm_mdiobus_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lan743x_mdiobus_read ; 
 int /*<<< orphan*/  lan743x_mdiobus_write ; 
 int mdiobus_register (TYPE_3__*) ; 
 char* pci_name (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int lan743x_mdiobus_init(struct lan743x_adapter *adapter)
{
	int ret;

	adapter->mdiobus = devm_mdiobus_alloc(&adapter->pdev->dev);
	if (!(adapter->mdiobus)) {
		ret = -ENOMEM;
		goto return_error;
	}

	adapter->mdiobus->priv = (void *)adapter;
	adapter->mdiobus->read = lan743x_mdiobus_read;
	adapter->mdiobus->write = lan743x_mdiobus_write;
	adapter->mdiobus->name = "lan743x-mdiobus";
	snprintf(adapter->mdiobus->id, MII_BUS_ID_SIZE,
		 "pci-%s", pci_name(adapter->pdev));

	if ((adapter->csr.id_rev & ID_REV_ID_MASK_) == ID_REV_ID_LAN7430_)
		/* LAN7430 uses internal phy at address 1 */
		adapter->mdiobus->phy_mask = ~(u32)BIT(1);

	/* register mdiobus */
	ret = mdiobus_register(adapter->mdiobus);
	if (ret < 0)
		goto return_error;
	return 0;

return_error:
	return ret;
}