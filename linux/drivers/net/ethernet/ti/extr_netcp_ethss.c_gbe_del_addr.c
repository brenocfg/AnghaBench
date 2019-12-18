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
struct netcp_addr {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct gbe_priv {int /*<<< orphan*/  dev; } ;
struct gbe_intf {struct gbe_priv* gbe_dev; } ;

/* Variables and functions */
#define  ADDR_ANY 132 
#define  ADDR_BCAST 131 
#define  ADDR_DEV 130 
#define  ADDR_MCAST 129 
#define  ADDR_UCAST 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbe_del_mcast_addr (struct gbe_intf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbe_del_ucast_addr (struct gbe_intf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gbe_del_addr(void *intf_priv, struct netcp_addr *naddr)
{
	struct gbe_intf *gbe_intf = intf_priv;
	struct gbe_priv *gbe_dev = gbe_intf->gbe_dev;

	dev_dbg(gbe_dev->dev, "ethss deleting address %pM, type %d\n",
		naddr->addr, naddr->type);

	switch (naddr->type) {
	case ADDR_MCAST:
	case ADDR_BCAST:
		gbe_del_mcast_addr(gbe_intf, naddr->addr);
		break;
	case ADDR_UCAST:
	case ADDR_DEV:
		gbe_del_ucast_addr(gbe_intf, naddr->addr);
		break;
	case ADDR_ANY:
		/* nothing to do for promiscuous */
	default:
		break;
	}

	return 0;
}