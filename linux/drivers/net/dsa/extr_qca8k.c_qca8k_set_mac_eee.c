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
typedef  int /*<<< orphan*/  u32 ;
struct qca8k_priv {int /*<<< orphan*/  reg_mutex; } ;
struct ethtool_eee {scalar_t__ eee_enabled; } ;
struct dsa_switch {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCA8K_REG_EEE_CTRL ; 
 int /*<<< orphan*/  QCA8K_REG_EEE_CTRL_LPI_EN (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qca8k_read (struct qca8k_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qca8k_write (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qca8k_set_mac_eee(struct dsa_switch *ds, int port, struct ethtool_eee *eee)
{
	struct qca8k_priv *priv = (struct qca8k_priv *)ds->priv;
	u32 lpi_en = QCA8K_REG_EEE_CTRL_LPI_EN(port);
	u32 reg;

	mutex_lock(&priv->reg_mutex);
	reg = qca8k_read(priv, QCA8K_REG_EEE_CTRL);
	if (eee->eee_enabled)
		reg |= lpi_en;
	else
		reg &= ~lpi_en;
	qca8k_write(priv, QCA8K_REG_EEE_CTRL, reg);
	mutex_unlock(&priv->reg_mutex);

	return 0;
}