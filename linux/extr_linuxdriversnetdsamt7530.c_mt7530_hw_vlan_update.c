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
struct mt7530_priv {int dummy; } ;
struct mt7530_hw_vlan_entry {int old_members; } ;
typedef  int /*<<< orphan*/  (* mt7530_vlan_op ) (struct mt7530_priv*,struct mt7530_hw_vlan_entry*) ;

/* Variables and functions */
 int /*<<< orphan*/  MT7530_VAWD1 ; 
 int /*<<< orphan*/  MT7530_VTCR_RD_VID ; 
 int /*<<< orphan*/  MT7530_VTCR_WR_VID ; 
 int PORT_MEM_MASK ; 
 int PORT_MEM_SHFT ; 
 int mt7530_read (struct mt7530_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_vlan_cmd (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7530_hw_vlan_update(struct mt7530_priv *priv, u16 vid,
		      struct mt7530_hw_vlan_entry *entry,
		      mt7530_vlan_op vlan_op)
{
	u32 val;

	/* Fetch entry */
	mt7530_vlan_cmd(priv, MT7530_VTCR_RD_VID, vid);

	val = mt7530_read(priv, MT7530_VAWD1);

	entry->old_members = (val >> PORT_MEM_SHFT) & PORT_MEM_MASK;

	/* Manipulate entry */
	vlan_op(priv, entry);

	/* Flush result to hardware */
	mt7530_vlan_cmd(priv, MT7530_VTCR_WR_VID, vid);
}