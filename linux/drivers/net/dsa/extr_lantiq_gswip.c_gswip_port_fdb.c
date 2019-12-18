#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct gswip_priv {int /*<<< orphan*/  dev; TYPE_3__* vlans; TYPE_1__* hw_info; } ;
struct gswip_pce_table_entry {int key_mode; unsigned char* key; int valid; int /*<<< orphan*/ * val; int /*<<< orphan*/  table; int /*<<< orphan*/  member_0; } ;
struct dsa_switch {struct gswip_priv* priv; } ;
struct TYPE_6__ {int fid; struct net_device* bridge; } ;
struct TYPE_5__ {struct net_device* bridge_dev; } ;
struct TYPE_4__ {unsigned int cpu_port; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GSWIP_TABLE_MAC_BRIDGE ; 
 int /*<<< orphan*/  GSWIP_TABLE_MAC_BRIDGE_STATIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* dsa_to_port (struct dsa_switch*,int) ; 
 int gswip_pce_table_entry_write (struct gswip_priv*,struct gswip_pce_table_entry*) ; 

__attribute__((used)) static int gswip_port_fdb(struct dsa_switch *ds, int port,
			  const unsigned char *addr, u16 vid, bool add)
{
	struct gswip_priv *priv = ds->priv;
	struct net_device *bridge = dsa_to_port(ds, port)->bridge_dev;
	struct gswip_pce_table_entry mac_bridge = {0,};
	unsigned int cpu_port = priv->hw_info->cpu_port;
	int fid = -1;
	int i;
	int err;

	if (!bridge)
		return -EINVAL;

	for (i = cpu_port; i < ARRAY_SIZE(priv->vlans); i++) {
		if (priv->vlans[i].bridge == bridge) {
			fid = priv->vlans[i].fid;
			break;
		}
	}

	if (fid == -1) {
		dev_err(priv->dev, "Port not part of a bridge\n");
		return -EINVAL;
	}

	mac_bridge.table = GSWIP_TABLE_MAC_BRIDGE;
	mac_bridge.key_mode = true;
	mac_bridge.key[0] = addr[5] | (addr[4] << 8);
	mac_bridge.key[1] = addr[3] | (addr[2] << 8);
	mac_bridge.key[2] = addr[1] | (addr[0] << 8);
	mac_bridge.key[3] = fid;
	mac_bridge.val[0] = add ? BIT(port) : 0; /* port map */
	mac_bridge.val[1] = GSWIP_TABLE_MAC_BRIDGE_STATIC;
	mac_bridge.valid = add;

	err = gswip_pce_table_entry_write(priv, &mac_bridge);
	if (err)
		dev_err(priv->dev, "failed to write mac bridge: %d\n", err);

	return err;
}