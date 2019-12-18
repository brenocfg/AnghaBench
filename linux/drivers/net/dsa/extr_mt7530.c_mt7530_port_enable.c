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
struct phy_device {int dummy; } ;
struct mt7530_priv {int /*<<< orphan*/  reg_mutex; TYPE_1__* ports; } ;
struct dsa_switch {struct mt7530_priv* priv; } ;
struct TYPE_2__ {int enable; int /*<<< orphan*/  pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT7530_CPU_PORT ; 
 int /*<<< orphan*/  MT7530_PCR_P (int) ; 
 int /*<<< orphan*/  PCR_MATRIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCR_MATRIX_MASK ; 
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  mt7530_port_set_status (struct mt7530_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_rmw (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt7530_port_enable(struct dsa_switch *ds, int port,
		   struct phy_device *phy)
{
	struct mt7530_priv *priv = ds->priv;

	if (!dsa_is_user_port(ds, port))
		return 0;

	mutex_lock(&priv->reg_mutex);

	/* Allow the user port gets connected to the cpu port and also
	 * restore the port matrix if the port is the member of a certain
	 * bridge.
	 */
	priv->ports[port].pm |= PCR_MATRIX(BIT(MT7530_CPU_PORT));
	priv->ports[port].enable = true;
	mt7530_rmw(priv, MT7530_PCR_P(port), PCR_MATRIX_MASK,
		   priv->ports[port].pm);
	mt7530_port_set_status(priv, port, 0);

	mutex_unlock(&priv->reg_mutex);

	return 0;
}