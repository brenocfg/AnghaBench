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
struct switchdev_obj_port_vlan {int flags; scalar_t__ vid_begin; scalar_t__ vid_end; } ;
struct mt7530_priv {int /*<<< orphan*/  reg_mutex; TYPE_1__* ports; } ;
struct mt7530_hw_vlan_entry {int dummy; } ;
struct dsa_switch {int /*<<< orphan*/ * ports; struct mt7530_priv* priv; } ;
struct TYPE_2__ {scalar_t__ pvid; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_PVID ; 
 int BRIDGE_VLAN_INFO_UNTAGGED ; 
 int /*<<< orphan*/  G0_PORT_VID (scalar_t__) ; 
 int /*<<< orphan*/  G0_PORT_VID_MASK ; 
 int /*<<< orphan*/  MT7530_PPBV1_P (int) ; 
 int /*<<< orphan*/  dsa_port_is_vlan_filtering (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt7530_hw_vlan_add ; 
 int /*<<< orphan*/  mt7530_hw_vlan_entry_init (struct mt7530_hw_vlan_entry*,int,int) ; 
 int /*<<< orphan*/  mt7530_hw_vlan_update (struct mt7530_priv*,scalar_t__,struct mt7530_hw_vlan_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_rmw (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt7530_port_vlan_add(struct dsa_switch *ds, int port,
		     const struct switchdev_obj_port_vlan *vlan)
{
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	struct mt7530_hw_vlan_entry new_entry;
	struct mt7530_priv *priv = ds->priv;
	u16 vid;

	/* The port is kept as VLAN-unaware if bridge with vlan_filtering not
	 * being set.
	 */
	if (!dsa_port_is_vlan_filtering(&ds->ports[port]))
		return;

	mutex_lock(&priv->reg_mutex);

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; ++vid) {
		mt7530_hw_vlan_entry_init(&new_entry, port, untagged);
		mt7530_hw_vlan_update(priv, vid, &new_entry,
				      mt7530_hw_vlan_add);
	}

	if (pvid) {
		mt7530_rmw(priv, MT7530_PPBV1_P(port), G0_PORT_VID_MASK,
			   G0_PORT_VID(vlan->vid_end));
		priv->ports[port].pvid = vlan->vid_end;
	}

	mutex_unlock(&priv->reg_mutex);
}