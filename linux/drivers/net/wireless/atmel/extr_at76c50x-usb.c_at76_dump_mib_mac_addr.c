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
struct mib_mac_addr {int mac_addr; int /*<<< orphan*/ * group_addr_status; int /*<<< orphan*/ * group_addr; int /*<<< orphan*/ * res; } ;
struct at76_priv {TYPE_1__* hw; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBG_MIB ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIB_MAC_ADDR ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int at76_get_mib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mib_mac_addr*,int) ; 
 int /*<<< orphan*/  kfree (struct mib_mac_addr*) ; 
 struct mib_mac_addr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at76_dump_mib_mac_addr(struct at76_priv *priv)
{
	int i;
	int ret;
	struct mib_mac_addr *m = kmalloc(sizeof(struct mib_mac_addr),
					 GFP_KERNEL);

	if (!m)
		return;

	ret = at76_get_mib(priv->udev, MIB_MAC_ADDR, m,
			   sizeof(struct mib_mac_addr));
	if (ret < 0) {
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MAC_ADDR) failed: %d\n", ret);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MAC_ADDR: mac_addr %pM res 0x%x 0x%x",
		 wiphy_name(priv->hw->wiphy),
		 m->mac_addr, m->res[0], m->res[1]);
	for (i = 0; i < ARRAY_SIZE(m->group_addr); i++)
		at76_dbg(DBG_MIB, "%s: MIB MAC_ADDR: group addr %d: %pM, "
			 "status %d", wiphy_name(priv->hw->wiphy), i,
			 m->group_addr[i], m->group_addr_status[i]);
exit:
	kfree(m);
}