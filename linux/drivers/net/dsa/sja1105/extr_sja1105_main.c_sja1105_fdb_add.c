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
typedef  int /*<<< orphan*/  u16 ;
struct sja1105_private {TYPE_1__* info; } ;
struct dsa_switch {int /*<<< orphan*/ * ports; struct sja1105_private* priv; } ;
struct TYPE_2__ {int (* fdb_add_cmd ) (struct dsa_switch*,int,unsigned char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_port_is_vlan_filtering (int /*<<< orphan*/ *) ; 
 int stub1 (struct dsa_switch*,int,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sja1105_fdb_add(struct dsa_switch *ds, int port,
			   const unsigned char *addr, u16 vid)
{
	struct sja1105_private *priv = ds->priv;

	/* dsa_8021q is in effect when the bridge's vlan_filtering isn't,
	 * so the switch still does some VLAN processing internally.
	 * But Shared VLAN Learning (SVL) is also active, and it will take
	 * care of autonomous forwarding between the unique pvid's of each
	 * port.  Here we just make sure that users can't add duplicate FDB
	 * entries when in this mode - the actual VID doesn't matter except
	 * for what gets printed in 'bridge fdb show'.  In the case of zero,
	 * no VID gets printed at all.
	 */
	if (!dsa_port_is_vlan_filtering(&ds->ports[port]))
		vid = 0;

	return priv->info->fdb_add_cmd(ds, port, addr, vid);
}