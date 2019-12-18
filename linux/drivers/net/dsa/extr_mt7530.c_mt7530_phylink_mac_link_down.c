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
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  mt7530_port_set_status (struct mt7530_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7530_phylink_mac_link_down(struct dsa_switch *ds, int port,
					 unsigned int mode,
					 phy_interface_t interface)
{
	struct mt7530_priv *priv = ds->priv;

	mt7530_port_set_status(priv, port, 0);
}