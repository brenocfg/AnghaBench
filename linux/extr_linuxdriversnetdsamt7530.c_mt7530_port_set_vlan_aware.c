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
struct mt7530_priv {int dummy; } ;
struct dsa_switch {struct mt7530_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7530_ALL_MEMBERS ; 
 int /*<<< orphan*/  MT7530_PCR_P (int) ; 
 int /*<<< orphan*/  MT7530_PORT_SECURITY_MODE ; 
 int /*<<< orphan*/  MT7530_PVC_P (int) ; 
 int /*<<< orphan*/  MT7530_VLAN_USER ; 
 int /*<<< orphan*/  PCR_MATRIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCR_MATRIX_MASK ; 
 int /*<<< orphan*/  PCR_PORT_VLAN_MASK ; 
 int /*<<< orphan*/  VLAN_ATTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLAN_ATTR_MASK ; 
 int /*<<< orphan*/  mt7530_rmw (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7530_port_set_vlan_aware(struct dsa_switch *ds, int port)
{
	struct mt7530_priv *priv = ds->priv;

	/* The real fabric path would be decided on the membership in the
	 * entry of VLAN table. PCR_MATRIX set up here with ALL_MEMBERS
	 * means potential VLAN can be consisting of certain subset of all
	 * ports.
	 */
	mt7530_rmw(priv, MT7530_PCR_P(port),
		   PCR_MATRIX_MASK, PCR_MATRIX(MT7530_ALL_MEMBERS));

	/* Trapped into security mode allows packet forwarding through VLAN
	 * table lookup.
	 */
	mt7530_rmw(priv, MT7530_PCR_P(port), PCR_PORT_VLAN_MASK,
		   MT7530_PORT_SECURITY_MODE);

	/* Set the port as a user port which is to be able to recognize VID
	 * from incoming packets before fetching entry within the VLAN table.
	 */
	mt7530_rmw(priv, MT7530_PVC_P(port), VLAN_ATTR_MASK,
		   VLAN_ATTR(MT7530_VLAN_USER));
}