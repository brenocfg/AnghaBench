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
typedef  scalar_t__ u16 ;
struct switchdev_obj_port_vlan {scalar_t__ vid_begin; scalar_t__ vid_end; } ;
struct mt7530_priv {int /*<<< orphan*/  reg_mutex; TYPE_1__* ports; } ;
struct mt7530_hw_vlan_entry {int dummy; } ;
struct dsa_switch {int /*<<< orphan*/ * ports; struct mt7530_priv* priv; } ;
struct TYPE_2__ {scalar_t__ pvid; } ;

/* Variables and functions */
 scalar_t__ G0_PORT_VID_DEF ; 
 int /*<<< orphan*/  G0_PORT_VID_MASK ; 
 int /*<<< orphan*/  MT7530_PPBV1_P (int) ; 
 int /*<<< orphan*/  dsa_port_is_vlan_filtering (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt7530_hw_vlan_del ; 
 int /*<<< orphan*/  mt7530_hw_vlan_entry_init (struct mt7530_hw_vlan_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_hw_vlan_update (struct mt7530_priv*,scalar_t__,struct mt7530_hw_vlan_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_rmw (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt7530_port_vlan_del(struct dsa_switch *ds, int port,
		     const struct switchdev_obj_port_vlan *vlan)
{
	struct mt7530_hw_vlan_entry target_entry;
	struct mt7530_priv *priv = ds->priv;
	u16 vid, pvid;

	/* The port is kept as VLAN-unaware if bridge with vlan_filtering not
	 * being set.
	 */
	if (!dsa_port_is_vlan_filtering(&ds->ports[port]))
		return 0;

	mutex_lock(&priv->reg_mutex);

	pvid = priv->ports[port].pvid;
	for (vid = vlan->vid_begin; vid <= vlan->vid_end; ++vid) {
		mt7530_hw_vlan_entry_init(&target_entry, port, 0);
		mt7530_hw_vlan_update(priv, vid, &target_entry,
				      mt7530_hw_vlan_del);

		/* PVID is being restored to the default whenever the PVID port
		 * is being removed from the VLAN.
		 */
		if (pvid == vid)
			pvid = G0_PORT_VID_DEF;
	}

	mt7530_rmw(priv, MT7530_PPBV1_P(port), G0_PORT_VID_MASK, pvid);
	priv->ports[port].pvid = pvid;

	mutex_unlock(&priv->reg_mutex);

	return 0;
}